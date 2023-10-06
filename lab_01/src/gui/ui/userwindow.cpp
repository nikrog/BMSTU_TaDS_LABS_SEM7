#include "userwindow.h"
#include "ui_userwindow.h"
#include "mainwindow.h"
#include <stdio.h>

UserWindow::UserWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                       GUIClientManager &clientmanager, GUIProductManager &productmanager,
                       GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->authManager = authmanager;
    this->managerManager = managermanager;
    this->clientManager = clientmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    ui->cur_type->addItem(trUtf8("Рубль"));
    ui->cur_type->addItem(trUtf8("Доллар"));
    ui->cur_type->addItem(trUtf8("Евро"));
    ui->cur_type->addItem(trUtf8("Юань"));
}

UserWindow::~UserWindow()
{
    delete ui;
}


void UserWindow::on_auth_clicked()
{
    this->logger->log(INFO, "Authorize button clicked by guest");
    this->close();
    MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
    w->show();
}

void UserWindow::on_search_clicked()
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
    f.bank_id = this->bankManager.getBankIDByName(bank), f.currency=i_cur;
    if ((!bank.empty()) && (f.bank_id == NONE))
    {
        messageBox.information(0, "Уведомление", "Не найдено ни одного продукта данного банка!");
        messageBox.setFixedSize(500,200);
    }

    if (this->ui->r1->isChecked())
        {
            f.sort_param = "rate";
            f.sort_dir = "DESC";
            this->logger->log(INFO, "Guest search deposites");
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(8);
            ui->tableWidget->setColumnWidth(0, 5);
            ui->tableWidget->setColumnWidth(1, 200);
            ui->tableWidget->setColumnWidth(2, 150);
            ui->tableWidget->setColumnWidth(3, 200);
            ui->tableWidget->setColumnWidth(4, 200);
            ui->tableWidget->setColumnWidth(5, 200);
            ui->tableWidget->setColumnWidth(6, 100);
            ui->tableWidget->setColumnWidth(7, 200);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                       << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                       << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг"));

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
                //auto button = new QToolButton(this);
                //button->setText("click me");
                //button->connect(button, QToolButton::click(), this, "handleClick");
                //ui->tableWidget->setCellWidget(i, 8, button);
            }
        }
        else if (this->ui->r2->isChecked())
        {
            f.sort_param = "rate";
            f.sort_dir = "ASC";
            this->logger->log(INFO, "Guest search credits");
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(8);
            ui->tableWidget->setColumnWidth(0, 5);
            ui->tableWidget->setColumnWidth(1, 200);
            ui->tableWidget->setColumnWidth(2, 150);
            ui->tableWidget->setColumnWidth(3, 200);
            ui->tableWidget->setColumnWidth(4, 200);
            ui->tableWidget->setColumnWidth(5, 200);
            ui->tableWidget->setColumnWidth(6, 100);
            ui->tableWidget->setColumnWidth(7, 200);
            ui->tableWidget->setShowGrid(true);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("#") \
                                                       << trUtf8("Название") << trUtf8("Банк") << trUtf8("Ставка") \
                                                       << trUtf8("Срок (дн.)") << trUtf8("Сумма") << trUtf8("Валюта") << trUtf8("Рейтинг"));
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
            }
        }
        else if (this->ui->r3->isChecked())
        {
            this->logger->log(INFO, "Guest search banks");
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
}

/*void UserWindow::handleClick()
{
    std::cout << "Hi";
}*/
