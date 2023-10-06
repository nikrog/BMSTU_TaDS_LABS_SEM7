#include "addbankwindow.h"
#include "ui_addbankwindow.h"
#include "mainwindow.h"

AddBankWindow::AddBankWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                             GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int u_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBankWindow)
{
    ui->setupUi(this);
    this->clientManager = clientmanager;
    this->authManager = authmanager;
    this->managerManager = managersmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->user_id = u_id;
}

AddBankWindow::~AddBankWindow()
{
    delete ui;
}

void AddBankWindow::on_enter_clicked()
{
    QMessageBox messageBox;
    BankInfo inf;
    std::string bank = this->ui->bankEdit->text().toStdString();
    std::string website = this->ui->websiteEdit->text().toStdString();
    std::string license = this->ui->licEdit->text().toStdString();
    std::string address = this->ui->addressEdit->text().toStdString();
    std::string email = this->ui->emailEdit->text().toStdString();
    std::string phone = this->ui->phoneEdit->text().toStdString();
    if (bank.empty() || website.empty() || address.empty() || email.empty() || phone.empty() || license.empty())
    {
        messageBox.critical(0, "Ошибка!", "Все поля должны быть заполнены!");
        messageBox.setFixedSize(500,200);
        return;
    }
    if (phone.length() != 12)
    {
        messageBox.critical(0, "Error", "Некорректная длина номера телефона!");
        messageBox.setFixedSize(500,200);
        return;
    }
    long int lic_num = std::stol(license);
    inf.name = bank;
    inf.website = website;
    inf.license_num = lic_num;
    inf.address = address;
    inf.email = email;
    inf.phone = phone;
    try
    {
        this->bankManager.addBank(inf);
        this->logger->log(INFO, "Admin added new bank");
        messageBox.information(0, "Успех!", "Банк успешно добавлен!");
        this->close();
        AdminWindow *w = new AdminWindow(this->authManager, this->managerManager, this->clientManager,
                                                           this->productManager, this->bankManager, this->requestManager, *this->logger, this->user_id);
        w->show();
    }
    catch (const std::exception &e)
    {
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
        return;
    }
}

void AddBankWindow::on_back_clicked()
{
    this->close();
    AdminWindow *w = new AdminWindow(this->authManager, this->managerManager, this->clientManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger, this->user_id);
    w->show();
}
