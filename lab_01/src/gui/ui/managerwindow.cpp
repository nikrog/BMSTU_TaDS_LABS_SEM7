#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "mainwindow.h"
#include "changepasswordwindow.h"
#include "addproductwindow.h"
#include "updateproductwindow.h"
#include "updateclientwindow.h"
#include "managerupdateclientwindow.h"

ManagerWindow::ManagerWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                             GUIClientManager &clientmanager, GUIProductManager &productmanager,
                             GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int man_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    this->authManager = authmanager;
    this->managerManager = managermanager;
    this->clientManager = clientmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->manager_id = man_id;
    ui->cur_type->addItem(trUtf8("Рубль"));
    ui->cur_type->addItem(trUtf8("Доллар"));
    ui->cur_type->addItem(trUtf8("Евро"));
    ui->cur_type->addItem(trUtf8("Юань"));
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_exit_clicked()
{
    this->logger->log(INFO, "Unauthorized button clicked by manager");
    this->close();
    MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
    w->show();
}

void ManagerWindow::on_search_clicked()
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
        this->logger->log(INFO, "Manager search deposites");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(10);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 200);
        ui->tableWidget->setColumnWidth(6, 100);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 220);
        ui->tableWidget->setColumnWidth(9, 150);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                   << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг")
                                                   << trUtf8("Действие") << trUtf8("Действие"));

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
            Manager m = this->managerManager.viewManager(this->manager_id);
            if (products[i].getBankID() == m.getBankID())
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createUpdateProdButtonWidget("Обновить данные", true));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 9),
                        createDeleteProdButtonWidget("Удалить", true));
            }
            else
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createUpdateProdButtonWidget("Обновить данные", false));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 9),
                        createDeleteProdButtonWidget("Удалить", false));
            }
        }
    }
    else if (this->ui->r2->isChecked())
    {
        f.sort_param = "rate";
        f.sort_dir = "ASC";
        this->logger->log(INFO, "Manager search credits");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(10);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 250);
        ui->tableWidget->setColumnWidth(6, 100);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 220);
        ui->tableWidget->setColumnWidth(9, 150);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                   << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                   << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг")
                                                   << trUtf8("Действие") << trUtf8("Действие"));
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
            Manager m = this->managerManager.viewManager(this->manager_id);
            if (products[i].getBankID() == m.getBankID())
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createUpdateProdButtonWidget("Обновить данные", true));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 9),
                        createDeleteProdButtonWidget("Удалить", true));
            }
            else
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 8),
                        createUpdateProdButtonWidget("Обновить данные", false));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 9),
                        createDeleteProdButtonWidget("Удалить", false));
            }
        }
    }
    else if (this->ui->r3->isChecked())
    {
        this->logger->log(INFO, "Manager search banks");
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
        this->logger->log(INFO, "Manager search bank requests");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(12);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 200);
        ui->tableWidget->setColumnWidth(3, 150);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 300);
        ui->tableWidget->setColumnWidth(6, 300);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 200);
        ui->tableWidget->setColumnWidth(9, 200);
        ui->tableWidget->setColumnWidth(10, 150);
        ui->tableWidget->setColumnWidth(11, 150);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") << trUtf8("№ клиента")
                                                   << trUtf8("№ продукта") << trUtf8("Сумма") << trUtf8("Срок (дн.)") \
                                                   << trUtf8("Дата") << trUtf8("Статус") << trUtf8("№ менеджера")
                                                   << trUtf8("Действие") << trUtf8("Действие") << trUtf8("Действие")
                                                   << trUtf8("Действие"));
        Manager man = this->managerManager.viewManager(this->manager_id);
        std::vector<Request> requests = this->requestManager.viewBankRequests(man.getBankID());
        for( size_t i = 0; i < requests.size(); i++)
        {
            std::string num = std::to_string(requests[i].getID());
            std::string cl_num = std::to_string(requests[i].getClientID());
            std::string p_num = std::to_string(requests[i].getProductID());
            std::string sum = std::to_string((int) requests[i].getSum());
            std::string dur = std::to_string(requests[i].getDuration());
            std::string r_date = requests[i].getDate();
            std::string state = states[requests[i].getState()];
            std::string man_id = std::to_string(requests[i].getManagerID());
            if (requests[i].getManagerID() == NONE)
                man_id = "не назначен";
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(cl_num.c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(p_num.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(sum.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(dur.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(r_date.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(state.c_str())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(man_id.c_str())));
            ui->tableWidget->setIndexWidget(
                    ui->tableWidget->model()->index(i, 8),
                    createReqHistoryButtonWidget("История клиента"));
            ui->tableWidget->setIndexWidget(
                    ui->tableWidget->model()->index(i, 9),
                    createClientInfoButtonWidget("Данные клиента"));
            if (requests[i].getState() == OPENED)
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 10),
                        createApproveReqButtonWidget("Одобрить", true));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 11),
                        createRejectReqButtonWidget("Отклонить", true));
                //qDebug() << "YES";
            }
            else
            {
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 10),
                        createApproveReqButtonWidget("Одобрить", false));
                ui->tableWidget->setIndexWidget(
                        ui->tableWidget->model()->index(i, 11),
                        createRejectReqButtonWidget("Отклонить", false));
            }
        }
    }
    else if (this->ui->r5->isChecked())
    {
        this->logger->log(INFO, "Manager search clients");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(10);
        ui->tableWidget->setColumnWidth(0, 5);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 200);
        ui->tableWidget->setColumnWidth(3, 150);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->setColumnWidth(5, 300);
        ui->tableWidget->setColumnWidth(6, 300);
        ui->tableWidget->setColumnWidth(7, 200);
        ui->tableWidget->setColumnWidth(8, 200);
        ui->tableWidget->setColumnWidth(9, 220);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") << trUtf8("Фамилия")
                                                   << trUtf8("Имя") << trUtf8("Отчество") << trUtf8("Паспорт") \
                                                   << trUtf8("Дата рождения") << trUtf8("Адрес проживания") << trUtf8("Email") << trUtf8("Телефон")
                                                   << trUtf8("Действие"));
        std::vector<Client> clients = this->clientManager.viewAllClients();
        for( size_t i = 0; i < clients.size(); i++)
        {
            std::string num = std::to_string(clients[i].getID());
            std::string name = clients[i].getName();
            std::string surname = clients[i].getSurname();
            std::string patr = clients[i].getPatronymic();
            std::string passport = std::to_string(clients[i].getPassportNum());
            std::string birth = this->clientManager.fromINTtoDate(clients[i].getBirthDate());
            std::string address = clients[i].getAddress();
            std::string email = clients[i].getEmail();
            std::string phone = clients[i].getPhone();
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(surname.c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(name.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(patr.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(passport.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(birth.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(address.c_str())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(email.c_str())));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString(phone.c_str())));
            ui->tableWidget->setIndexWidget(
                    ui->tableWidget->model()->index(i, 9),
                    createUpdateClientButtonWidget("Обновить данные"));
        }
    }
}

void ManagerWindow::on_cl_history_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->cl_num->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер клиента не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int cl_id = std::stoi(s_id);
    std::vector<std::string> states = {"Открыта", "Одобрена", "Отклонена", "Одобрена (оценена)", "Закрыта (оценена)", "Закрыта"};
    std::vector<std::string> ptypes = {"Депозит", "Кредит"};
    this->logger->log(INFO, "Manager search client history");
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setColumnWidth(0, 5);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 200);
    ui->tableWidget->setColumnWidth(5, 300);
    ui->tableWidget->setColumnWidth(6, 300);
    ui->tableWidget->setColumnWidth(7, 200);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                               << trUtf8("№ продукта") << trUtf8("Тип") << trUtf8("Сумма") << trUtf8("Срок (дн.)") \
                                               << trUtf8("Дата") << trUtf8("Статус") << trUtf8("№ менеджера"));
    std::vector<Request> requests = this->requestManager.viewMyRequests(cl_id);
    for( size_t i = 0; i < requests.size(); i++)
    {
        std::string num = std::to_string(requests[i].getID());
        Product p = this->productManager.viewProduct(requests[i].getProductID());
        std::string ptype = ptypes[p.getType()];
        std::string p_num = std::to_string(requests[i].getProductID());
        std::string sum = std::to_string((int) requests[i].getSum());
        std::string dur = std::to_string(requests[i].getDuration());
        std::string r_date = requests[i].getDate();
        std::string state = states[requests[i].getState()];
        std::string man_id = std::to_string(requests[i].getManagerID());
        if (requests[i].getManagerID() == NONE)
            man_id = "не назначен";
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(p_num.c_str())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(ptype.c_str())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(sum.c_str())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(dur.c_str())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(r_date.c_str())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(state.c_str())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(man_id.c_str())));
    }
}

void ManagerWindow::on_approve_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->num_req->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер заявки не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int req_id = std::stoi(s_id);
    try
    {
        this->requestManager.confirmRequest(req_id, this->manager_id);
        this->logger->log(INFO, "Manager approved request success");
        messageBox.information(0, "Успех!", "Заявка одобрена успешно!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
}

void ManagerWindow::on_reject_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->num_req->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер заявки не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int req_id = std::stoi(s_id);
    try
    {
        this->requestManager.rejectRequest(req_id, this->manager_id);
        this->logger->log(INFO, "Manager rejected request success");
        messageBox.information(0, "Успех!", "Заявка отклонена успешно!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
}

void ManagerWindow::on_update_password_clicked()
{
    this->logger->log(INFO, "Manager requested change password");
    Manager m = this->managerManager.viewManager(this->manager_id);
    this->close();
    ChangePasswordWindow *w = new ChangePasswordWindow(this->authManager, this->clientManager, this->managerManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger, m.getUserID(), this->manager_id);
    w->show();
}

void ManagerWindow::on_delete_manager_clicked()
{
    QMessageBox messageBox;
    int ans = messageBox.question(0, "Предупреждение", "Вы действительно хотите удалить свой аккаунт?", "Да", "Нет");
    if (ans == 0)
    {
        Manager m = this->managerManager.viewManager(this->manager_id);
        this->authManager.deleteUser(m.getUserID());
        this->logger->log(INFO, "Manager deleted own account");
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

void ManagerWindow::on_delete_product_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->prod_num->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер продукта не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int p_num = std::stoi(s_id);
    try
    {
        Product p = this->productManager.viewProduct(p_num);
        Manager m = this->managerManager.viewManager(this->manager_id);
        if (m.getBankID() != p.getBankID())
        {
            this->logger->log(ERROR, "Manager can not delete product from another bank");
            messageBox.critical(0, "Ошибка!", "Продукт другого банка не может быть удален!");
            messageBox.setFixedSize(500,200);
            return;
        }
        this->productManager.deleteProduct(p_num);
        this->logger->log(INFO, "Manager deleted product success");
        messageBox.information(0, "Успех!", "Продукт удален успешно!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
}

void ManagerWindow::on_update_product_clicked()
{
    QMessageBox messageBox;
    std::string s_id = this->ui->prod_num->text().toStdString();
    if (s_id.empty())
    {
        messageBox.critical(0, "Ошибка!", "Номер продукта не задан!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int prod_id = std::stoi(s_id);
    try
    {
        Product p = this->productManager.viewProduct(prod_id);
        Manager m = this->managerManager.viewManager(this->manager_id);
        if (p.getBankID() != m.getBankID())
        {
            messageBox.critical(0, "Ошибка!", "Нельзя изменить продукт другого банка!");
            messageBox.setFixedSize(500,200);
            return;
        }
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
        return;
    }
    this->logger->log(INFO, "Manager requested update product");
    this->close();
    UpdateProductWindow *w = new UpdateProductWindow(this->authManager, this->clientManager, this->managerManager,
                                         this->productManager, this->bankManager, this->requestManager, *this->logger, this->manager_id, prod_id);
    w->show();
}

void ManagerWindow::on_add_product_clicked()
{
    this->logger->log(INFO, "Manager requested add new product");
    this->close();
    AddProductWindow *w = new AddProductWindow(this->authManager, this->clientManager, this->managerManager, this->productManager,
                               this->bankManager, this->requestManager, *this->logger, this->manager_id);
    w->show();
}

void ManagerWindow::onApproveReqBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int req_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            try
            {
                this->requestManager.confirmRequest(req_id, this->manager_id);
                this->logger->log(INFO, "Manager approved request success");
                messageBox.information(0, "Успех!", "Заявка одобрена успешно!");
                messageBox.setFixedSize(500,200);
            }
            catch (const std::exception &e)
            {
                this->logger->log(ERROR, std::string("Error: ") + e.what());
                messageBox.critical(0, "Ошибка!", e.what());
                messageBox.setFixedSize(500,200);
            }
        }
}

void ManagerWindow::onRejectReqBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int req_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            try
            {
                this->requestManager.rejectRequest(req_id, this->manager_id);
                this->logger->log(INFO, "Manager rejected request success");
                messageBox.information(0, "Успех!", "Заявка отклонена успешно!");
                messageBox.setFixedSize(500,200);
            }
            catch (const std::exception &e)
            {
                this->logger->log(ERROR, std::string("Error: ") + e.what());
                messageBox.critical(0, "Ошибка!", e.what());
                messageBox.setFixedSize(500,200);
            }
        }
}

void ManagerWindow::onClientHistoryBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int cl_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 1)).toInt();
            std::vector<std::string> states = {"Открыта", "Одобрена", "Отклонена", "Одобрена (оценена)", "Закрыта (оценена)", "Закрыта"};
            std::vector<std::string> ptypes = {"Депозит", "Кредит"};
            this->logger->log(INFO, "Manager search client history");
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(8);
            ui->tableWidget->setColumnWidth(0, 5);
            ui->tableWidget->setColumnWidth(1, 200);
            ui->tableWidget->setColumnWidth(2, 150);
            ui->tableWidget->setColumnWidth(3, 150);
            ui->tableWidget->setColumnWidth(4, 200);
            ui->tableWidget->setColumnWidth(5, 300);
            ui->tableWidget->setColumnWidth(6, 300);
            ui->tableWidget->setColumnWidth(7, 200);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                       << trUtf8("№ продукта") << trUtf8("Тип") << trUtf8("Сумма") << trUtf8("Срок (дн.)") \
                                                       << trUtf8("Дата") << trUtf8("Статус") << trUtf8("№ менеджера"));
            std::vector<Request> requests = this->requestManager.viewMyRequests(cl_id);
            for( size_t i = 0; i < requests.size(); i++)
            {
                std::string num = std::to_string(requests[i].getID());
                Product p = this->productManager.viewProduct(requests[i].getProductID());
                std::string ptype = ptypes[p.getType()];
                std::string p_num = std::to_string(requests[i].getProductID());
                std::string sum = std::to_string((int) requests[i].getSum());
                std::string dur = std::to_string(requests[i].getDuration());
                std::string r_date = requests[i].getDate();
                std::string state = states[requests[i].getState()];
                std::string man_id = std::to_string(requests[i].getManagerID());
                if (requests[i].getManagerID() == NONE)
                    man_id = "не назначен";
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(p_num.c_str())));
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(ptype.c_str())));
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(sum.c_str())));
                ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(dur.c_str())));
                ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(r_date.c_str())));
                ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(state.c_str())));
                ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(man_id.c_str())));
            }
        }
}

void ManagerWindow::onClientInfoBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int cl_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 1)).toInt();
            this->logger->log(INFO, "Manager search clients");
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(9);
            ui->tableWidget->setColumnWidth(0, 5);
            ui->tableWidget->setColumnWidth(1, 200);
            ui->tableWidget->setColumnWidth(2, 200);
            ui->tableWidget->setColumnWidth(3, 150);
            ui->tableWidget->setColumnWidth(4, 200);
            ui->tableWidget->setColumnWidth(5, 300);
            ui->tableWidget->setColumnWidth(6, 300);
            ui->tableWidget->setColumnWidth(7, 200);
            ui->tableWidget->setColumnWidth(8, 200);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") << trUtf8("Фамилия")
                                                       << trUtf8("Имя") << trUtf8("Отчество") << trUtf8("Паспорт") \
                                                       << trUtf8("Дата рождения") << trUtf8("Адрес проживания") << trUtf8("Email") << trUtf8("Телефон"));
            Client cl = this->clientManager.viewClient(cl_id);
            int i = 0;
            std::string num = std::to_string(cl.getID());
            std::string name = cl.getName();
            std::string surname = cl.getSurname();
            std::string patr = cl.getPatronymic();
            std::string passport = std::to_string(cl.getPassportNum());
            std::string birth = this->clientManager.fromINTtoDate(cl.getBirthDate());
            std::string address = cl.getAddress();
            std::string email = cl.getEmail();
            std::string phone = cl.getPhone();
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(surname.c_str())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(name.c_str())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(patr.c_str())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString(passport.c_str())));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(birth.c_str())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(address.c_str())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(email.c_str())));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString(phone.c_str())));

        }
}

void ManagerWindow::onUpdateProdBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int prod_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            try
            {
                Product p = this->productManager.viewProduct(prod_id);
                Manager m = this->managerManager.viewManager(this->manager_id);
                if (p.getBankID() != m.getBankID())
                {
                    messageBox.critical(0, "Ошибка!", "Нельзя изменить продукт другого банка!");
                    messageBox.setFixedSize(500,200);
                    return;
                }
            }
            catch (const std::exception &e)
            {
                this->logger->log(ERROR, std::string("Error: ") + e.what());
                messageBox.critical(0, "Ошибка!", e.what());
                messageBox.setFixedSize(500,200);
                return;
            }
            this->logger->log(INFO, "Manager requested update product");
            this->close();
            UpdateProductWindow *w = new UpdateProductWindow(this->authManager, this->clientManager, this->managerManager,
                                                 this->productManager, this->bankManager, this->requestManager, *this->logger, this->manager_id, prod_id);
            w->show();
        }
}


void ManagerWindow::onDeleteProdBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int p_num = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            try
            {
                Product p = this->productManager.viewProduct(p_num);
                Manager m = this->managerManager.viewManager(this->manager_id);
                if (m.getBankID() != p.getBankID())
                {
                    this->logger->log(ERROR, "Manager can not delete product from another bank");
                    messageBox.critical(0, "Ошибка!", "Продукт другого банка не может быть удален!");
                    messageBox.setFixedSize(500,200);
                    return;
                }
                this->productManager.deleteProduct(p_num);
                this->logger->log(INFO, "Manager deleted product success");
                messageBox.information(0, "Успех!", "Продукт удален успешно!");
                messageBox.setFixedSize(500,200);
            }
            catch (const std::exception &e)
            {
                this->logger->log(ERROR, std::string("Error: ") + e.what());
                messageBox.critical(0, "Ошибка!", e.what());
                messageBox.setFixedSize(500,200);
            }
        }
}

void ManagerWindow::onUpdateClientBtnClicked()
{
    QMessageBox messageBox;
    if( QPushButton* btn = qobject_cast<QPushButton*>( sender() ) ) {
            QModelIndex index = ui->tableWidget->indexAt(btn->parentWidget()->pos());
            int cl_id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(index.row(), 0)).toInt();
            this->logger->log(INFO, "Manger update client attempt");
            this->close();
            ManagerUpdateClientWindow *w = new ManagerUpdateClientWindow(this->authManager, this->clientManager, this->managerManager, this->productManager,
                                                                 this->bankManager, this->requestManager, *this->logger, cl_id, this->manager_id);
            w->show();
        }
}

QWidget* ManagerWindow::createApproveReqButtonWidget(char* name, bool enable) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onApproveReqBtnClicked()));
    btn->setEnabled(enable);
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createRejectReqButtonWidget(char* name, bool enable) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onRejectReqBtnClicked()));
    btn->setEnabled(enable);
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createReqHistoryButtonWidget(char* name) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onClientHistoryBtnClicked()));
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createClientInfoButtonWidget(char* name) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onClientInfoBtnClicked()));
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createDeleteProdButtonWidget(char* name, bool enable) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onDeleteProdBtnClicked()));
    btn->setEnabled(enable);
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createUpdateProdButtonWidget(char* name, bool enable) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onUpdateProdBtnClicked()));
    btn->setEnabled(enable);
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}

QWidget* ManagerWindow::createUpdateClientButtonWidget(char* name) const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton(name);
    connect( btn, SIGNAL( clicked( bool ) ), SLOT(onUpdateClientBtnClicked()));
    l->setMargin(0);
    l->addWidget(btn);
    l->addStretch();
    wgt->setLayout(l);

    return wgt;
}
