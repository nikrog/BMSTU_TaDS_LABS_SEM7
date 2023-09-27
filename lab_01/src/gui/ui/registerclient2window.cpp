#include "registerclient2window.h"
#include "registerclientwindow.h"
#include "ui_registerclient2window.h"
#include "mainwindow.h"

RegisterClient2Window::RegisterClient2Window(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                                             GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, std::string login,
                                             std::string password, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterClient2Window)
{
    ui->setupUi(this);
    this->clientManager = clientmanager;
    this->authManager = authmanager;
    this->managerManager = managersmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->login = login;
    this->password = password;
}

RegisterClient2Window::~RegisterClient2Window()
{
    delete ui;
}

void RegisterClient2Window::on_enter_clicked()
{
    QMessageBox messageBox;
    ClientInfo inf;
    std::string name = this->ui->nameEdit->text().toStdString();
    std::string surname = this->ui->surnameEdit->text().toStdString();
    std::string patronymic = this->ui->patronymicEdit->text().toStdString();
    std::string passport = this->ui->passportEdit->text().toStdString();
    std::string address = this->ui->addressEdit->text().toStdString();
    std::string email = this->ui->emailEdit->text().toStdString();
    std::string phone = this->ui->phoneEdit->text().toStdString();
    std::string year = this->ui->dateEdit->date().toString("yyyy").toStdString();
    std::string month = this->ui->dateEdit->date().toString("MM").toStdString();
    std::string day = this->ui->dateEdit->date().toString("dd").toStdString();
    int birthdate = this->clientManager.fromDateToINT(year, month, day);
    if (name.empty() || surname.empty() || patronymic.empty() || address.empty() || email.empty() || phone.empty() || passport.empty())
    {
        messageBox.critical(0, "Error", "Все поля должны быть заполнены!");
        messageBox.setFixedSize(500,200);
        return;
    }
    if (passport.length() != 10)
    {
        messageBox.critical(0, "Error", "Некорректная длина номера паспорта!");
        messageBox.setFixedSize(500,200);
        return;
    }
    if (phone.length() != 12)
    {
        messageBox.critical(0, "Error", "Некорректная длина номера телефона!");
        messageBox.setFixedSize(500,200);
        return;
    }
    long int p_num = std::stol(passport);
    inf.user_id = NONE;
    inf.name = name;
    inf.surname = surname;
    inf.patronymic = patronymic;
    inf.passport_num = p_num;
    inf.address = address;
    inf.email = email;
    inf.phone = phone;
    inf.birth_date = birthdate;
    try
    {
        this->clientManager.addClient(inf, this->login, this->password);
    }
    catch (const std::exception &e)
    {
        messageBox.critical(0, "Error", e.what());
        messageBox.setFixedSize(500,200);
        return;
    }
    this->logger->log(INFO, "Register new client");
    messageBox.information(0, "Успех!", "Удалось успешно зарегистрироваться!");
    this->close();
    MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager,
                                   this->productManager, this->bankManager, this->requestManager, *this->logger);
    w->show();
}

void RegisterClient2Window::on_back_clicked()
{
    this->close();
    RegisterClientWindow *w = new RegisterClientWindow(this->authManager, this->clientManager, this->managerManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger);
    w->show();
}
