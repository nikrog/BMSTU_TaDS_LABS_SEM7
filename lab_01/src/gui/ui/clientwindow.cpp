#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "mainwindow.h"
#include "updateclientwindow.h"
#include "makerequestwindow.h"
#include "rateproductwindow.h"

ClientWindow::ClientWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                           GUIClientManager &clientmanager, GUIProductManager &productmanager,
                           GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int cl_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    this->authManager = authmanager;
    this->managerManager = managermanager;
    this->clientManager = clientmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->client_id = cl_id;
    ui->cur_type->addItem(trUtf8("Рубль"));
    ui->cur_type->addItem(trUtf8("Доллар"));
    ui->cur_type->addItem(trUtf8("Евро"));
    ui->cur_type->addItem(trUtf8("Юань"));
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_exit_clicked()
{
    this->logger->log(INFO, "Unauthorized button clicked by client");
    this->close();
    MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
    w->show();
}

void ClientWindow::on_search_clicked()
{
    std::vector<std::string> vals = {"Рубль", "Доллар", "Евро", "Юань"};
    QMessageBox messageBox;
    std::string name = this->ui->nameEdit->text().toStdString();
    std::string bank = this->ui->bankEdit->text().toStdString();
    float min_sum = this->ui->min_sum->value();
    float max_sum = this->ui->max_sum->value();
    float min_rate = this->ui->min_rate->value();
    float max_rate = this->ui->max_rate->value();
    int min_time = this->ui->min_time->value();
    int max_time = this->ui->max_time->value();
    float min_rating = this->ui->min_rating->value();
    std::string currency = this->ui->cur_type->currentText().toStdString();
    Curtype i_cur = ROUBLE;
    for (size_t i = 0; i < vals.size(); i++)
    {
        if (vals[i] == currency)
            i_cur = (Curtype) i;
    }
    ProductFilter f;
    f.min_sum = min_sum, f.max_sum = max_sum, f.min_rate = min_rate, f.max_rate = max_rate,
    f.min_time = min_time, f.max_time = max_time, f.avg_rating = min_rating, f.name = name;
    f.bank_id = this->bankManager.getBankIDByName(bank), f.currency = i_cur;
    if ((!bank.empty()) && (f.bank_id == NONE))
    {
        messageBox.information(0, "Уведомление", "Не найдено ни одного продукта данного банка!");
        messageBox.setFixedSize(500,200);
    }

    if (this->ui->r1->isChecked())
    {
        f.sort_param = "rate";
        f.sort_dir = "DESC";
        this->logger->log(INFO, "Client search deposites");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 200);
        ui->tableWidget->setColumnWidth(6, 100);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 170);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                   << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг")
                                                   << trUtf8("Действие"));

        //std::vector<Product> products = this->productManager.viewProductsByType(DEPOSIT);
        f.type = DEPOSIT;
        std::vector<Product> products = this->productManager.viewFilterProducts(f);
        for( size_t i = 0; i < products.size(); i++)
        {
            char buf[50];
            snprintf(buf, sizeof(buf), "%.1f", products[i].getRate());
            std::string rate(buf);
            //std::string rate = std::to_string(products[i].getRate());
            std::string num = std::to_string(products[i].getID());
            std::string dur = std::to_string(products[i].getMinTime()) + "-" + std::to_string(products[i].getMaxTime());
            std::string sum = std::to_string((int) products[i].getMinSum()) + "-" + std::to_string((int) products[i].getMaxSum());
            snprintf(buf, sizeof(buf), "%.2f", products[i].getAvgRating());
            std::string rating(buf);
            //std::string rating = std::to_string(products[i].getAvgRating());
            std::string bank = this->bankManager.getBankNameByID(products[i].getBankID());
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(products[i].getName().c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(bank.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(rate.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(dur.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(sum.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(vals[products[i].getCurrency()].c_str())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(rating.c_str())));
            ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createButtonWidget("Подать заявку"));
        }
    }
    else if (this->ui->r2->isChecked())
    {
        f.sort_param = "rate";
        f.sort_dir = "ASC";
        this->logger->log(INFO, "Client search credits");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 250);
        ui->tableWidget->setColumnWidth(6, 100);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 170);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                   << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг")
                                                   << trUtf8("Действие"));
        f.type = CREDIT;
        //std::vector<Product> products = this->productManager.viewProductsByType(CREDIT);
        std::vector<Product> products = this->productManager.viewFilterProducts(f);

        for( size_t i = 0; i < products.size(); i++)
        {
            char buf[50];
            snprintf(buf, sizeof(buf), "%.1f", products[i].getRate());
            std::string rate(buf);
            //std::string rate = std::to_string(products[i].getRate());
            std::string num = std::to_string(products[i].getID());
            std::string dur = std::to_string(products[i].getMinTime()) + "-" + std::to_string(products[i].getMaxTime());
            std::string sum = std::to_string((int) products[i].getMinSum()) + "-" + std::to_string((int) products[i].getMaxSum());
            snprintf(buf, sizeof(buf), "%.2f", products[i].getAvgRating());
            std::string rating(buf);
            //std::string rating = std::to_string(products[i].getAvgRating());
            std::string bank = this->bankManager.getBankNameByID(products[i].getBankID());
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(products[i].getName().c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(bank.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(rate.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(dur.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(sum.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(vals[products[i].getCurrency()].c_str())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(rating.c_str())));
            ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createButtonWidget("Подать заявку"));
        }
    }
    else if (this->ui->r3->isChecked())
    {
        this->logger->log(INFO, "Client search banks");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 200);
        ui->tableWidget->setColumnWidth(6, 300);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название") << trUtf8("Лицензия") << trUtf8("Адрес") \
                                                   << trUtf8("Email") << trUtf8("Телефон") << trUtf8("Сайт"));
        std::vector<Bank> banks = this->bankManager.printAllBanks();

        for( size_t i = 0; i < banks.size(); i++)
        {
            std::string lic = std::to_string(banks[i].getLicenseNum());
            std::string num = std::to_string(banks[i].getID());
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(banks[i].getName().c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(lic.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(banks[i].getAddress().c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(banks[i].getEmail().c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(banks[i].getPhone().c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(banks[i].getWebsite().c_str())));
        }
    }
    else if (this->ui->r4->isChecked())
    {
        std::vector<std::string> states = {"Открыта", "Одобрена", "Отклонена", "Одобрена (оценена)", "Закрыта (оценена)", "Закрыта"};
        this->logger->log(INFO, "Client search own requests");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(8);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 250);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 300);
        ui->tableWidget->setColumnWidth(5, 300);
        ui->tableWidget->setColumnWidth(6, 200);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название продукта") << trUtf8("Сумма") << trUtf8("Срок (дн.)") \
                                                   << trUtf8("Дата") << trUtf8("Статус") << trUtf8("№ менеджера")
                                                   << trUtf8("Действие"));
        std::vector<Request> requests = this->requestManager.viewMyRequests(this->client_id);
        for( size_t i = 0; i < requests.size(); i++)
        {
            std::string num = std::to_string(requests[i].getID());
            //std::string p_num = std::to_string(requests[i].getProductID());
            Product p = this->productManager.viewProduct(requests[i].getProductID());
            std::string p_name = p.getName();
            std::string sum = std::to_string((int) requests[i].getSum());
            std::string dur = std::to_string(requests[i].getDuration());
            std::string r_date = requests[i].getDate();
            std::string state = states[requests[i].getState()];
            std::string man_id = std::to_string(requests[i].getManagerID());
            if (requests[i].getManagerID() == NONE)
                man_id = "не назначен";
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(p_name.c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(sum.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(dur.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(r_date.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(state.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(man_id.c_str())));
            if ((requests[i].getState() == APPROVED) || (requests[i].getState() == CLOSED))
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 7),
                        createRateButtonWidget("Оценить продукт", true));
                //qDebug() << "YES";
            }
            else
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 7),
                        createRateButtonWidget("Оценить продукт", false));
            }
        }
    }
}

void ClientWindow::on_make_request_clicked()
{
    QMessageBox messageBox;
    RequestInfo inf;
    std::string s_id = this->ui->prod_num->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер продукта не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int p_id = std::stoi(s_id);
    float sum = this->ui->sum_req->value();
    float dur = this->ui->time_req->value();
    Client cl = this->clientManager.viewClient(this->client_id);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", now);
    std::string date(buffer);
    //std::cout << date;
    inf.client_id = this->client_id;
    inf.product_id = p_id;
    inf.sum = sum;
    inf.duration = dur;
    inf.date = date;
    inf.manager_id = NONE;
    inf.state = OPENED;
    try
    {
        this->requestManager.makeRequest(cl.getUserID(), inf);
        messageBox.information(0, "Успех!", "Заявка успешно подана!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
}

void ClientWindow::on_score_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->num_req->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер заявки не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int r_id = std::stoi(s_id);
    int score = this->ui->score_req->value();
    Client cl = this->clientManager.viewClient(this->client_id);
    try
    {
        this->requestManager.rateProduct(r_id, cl.getUserID(), score);
        messageBox.information(0, "Успех!", "Продукт оценен успешно!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
}

void ClientWindow::on_delete_client_clicked()
{
    QMessageBox messageBox;
    int ans = messageBox.question(0, "Предупреждение", "Вы действительно хотите удалить свой аккаунт?", "Да", "Нет");
    if (ans == 0)
    {
        Client cl = this->clientManager.viewClient(this->client_id);
        this->authManager.deleteUser(cl.getUserID());
        this->logger->log(INFO, "Client deleted own account");
        messageBox.information(0, "Успех!", "Ваш аккаунт успешно удален!");
        messageBox.setFixedSize(500,200);
        this->close();
        MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
        w->show();
    }
    else if (ans == 1)
    {
        return;
    }
}

void ClientWindow::on_update_client_clicked()
{
    this->logger->log(INFO, "Client update attempt");
    this->close();
    UpdateClientWindow *w = new UpdateClientWindow(this->authManager, this->clientManager, this->managerManager, this->productManager,
                                                         this->bankManager, this->requestManager, *this->logger, this->client_id);
    w->show();
}

void ClientWindow::onMakeReqBtnClicked()
{
    QMessageBox messageBox;
    //messageBox.information(0, "Успех!", "Подать заявку!");
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            //qDebug() << index.row() << "x" << index.column();
            /*QStringList name;
            for( int i = 0; i < 1; ++i) {
                name << ui->tableWidget->model()->data(
                         ui->tableWidget->model()->index(index.row(), i )
                     ).toString();
            }
            QMessageBox::information( this, "The button was clicked", name.join( " " ) );*/
            int p_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            MakeRequestWindow *w = new MakeRequestWindow(this->authManager, this->managerManager,  this->clientManager, this->productManager,
                                                                 this->bankManager, this->requestManager, *this->logger, this->client_id, p_id);
            w->show();
        }
}

void ClientWindow::onRateBtnClicked()
{
    QMessageBox messageBox;
    //messageBox.information(0, "Успех!", "Подать заявку!");
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            //qDebug() << index.row() << "x" << index.column();
            /*QStringList name;
            for( int i = 0; i < 1; ++i) {
                name << ui->tableWidget->model()->data(
                         ui->tableWidget->model()->index(index.row(), i )
                     ).toString();
            }
            QMessageBox::information( this, "The button was clicked", name.join( " " ) );*/
            int r_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            RateProductWindow *w = new RateProductWindow(this->authManager, this->managerManager,  this->clientManager, this->productManager,
                                                                 this->bankManager, this->requestManager, *this->logger, this->client_id, r_id);
            w->show();
        }
}

QWidget* ClientWindow::createButtonWidget(char* name) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onMakeReqBtnClicked()));
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ClientWindow::createRateButtonWidget(char* name, bool enable) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onRateBtnClicked()));
    btn->setEnabled(enable);
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}
