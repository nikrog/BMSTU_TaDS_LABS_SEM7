#include "updatebankwindow.h"
#include "ui_updatebankwindow.h"
#include "adminwindow.h"

UpdateBankWindow::UpdateBankWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                                   GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int u_id, int b_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateBankWindow)
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
    this->bank_id = b_id;
    Bank b = this->bankManager.viewBank(this->bank_id);
    this->ui->bankEdit->setPlaceholderText(trUtf8(b.getName().c_str()));
    this->ui->websiteEdit->setPlaceholderText(trUtf8(b.getWebsite().c_str()));
    this->ui->addressEdit->setPlaceholderText(trUtf8(b.getAddress().c_str()));
    this->ui->emailEdit->setPlaceholderText(trUtf8(b.getEmail().c_str()));
    this->ui->phoneEdit->setPlaceholderText(trUtf8(b.getPhone().c_str()));
    this->ui->licEdit->setPlaceholderText(trUtf8(std::to_string(b.getLicenseNum()).c_str()));
}

UpdateBankWindow::~UpdateBankWindow()
{
    delete ui;
}

void UpdateBankWindow::on_enter_clicked()
{
    QMessageBox messageBox;
    BankInfo inf;
    std::string bank = this->ui->bankEdit->text().toStdString();
    std::string website = this->ui->websiteEdit->text().toStdString();
    std::string license = this->ui->licEdit->text().toStdString();
    std::string address = this->ui->addressEdit->text().toStdString();
    std::string email = this->ui->emailEdit->text().toStdString();
    std::string phone = this->ui->phoneEdit->text().toStdString();
    /*if (bank.empty() || website.empty() || address.empty() || email.empty() || phone.empty() || license.empty())
    {
        messageBox.critical(0, "Ошибка!", "Все поля должны быть заполнены!");
        messageBox.setFixedSize(500,200);
        return;
    }*/
    long int lic_num;
    if (license.empty())
        lic_num = NONE;
    else
        lic_num = std::stol(license);
    inf.name = bank;
    inf.website = website;
    inf.license_num = lic_num;
    inf.address = address;
    inf.email = email;
    inf.phone = phone;
    try
    {
        this->bankManager.updateBank(this->bank_id, inf);
        this->logger->log(INFO, "Admin updated new bank");
        messageBox.information(0, "Успех!", "Банк успешно обновлен!");
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

void UpdateBankWindow::on_back_clicked()
{
    this->close();
    AdminWindow *w = new AdminWindow(this->authManager, this->managerManager, this->clientManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger, this->user_id);
    w->show();
}
