#include "updateclientwindow.h"
#include "ui_updateclientwindow.h"
#include "mainwindow.h"

UpdateClientWindow::UpdateClientWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                                       GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int cl_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateClientWindow)
{
    ui->setupUi(this);
    this->clientManager = clientmanager;
    this->authManager = authmanager;
    this->managerManager = managersmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->client_id = cl_id;
    Client cl = this->clientManager.viewClient(this->client_id);
    this->ui->nameEdit->setPlaceholderText(trUtf8(cl.getName().c_str()));
    this->ui->surnameEdit->setPlaceholderText(trUtf8(cl.getSurname().c_str()));
    this->ui->patronymicEdit->setPlaceholderText(trUtf8(cl.getPatronymic().c_str()));
    this->ui->addressEdit->setPlaceholderText(trUtf8(cl.getAddress().c_str()));
    this->ui->emailEdit->setPlaceholderText(trUtf8(cl.getEmail().c_str()));
    this->ui->phoneEdit->setPlaceholderText(trUtf8(cl.getPhone().c_str()));
    this->ui->passportEdit->setPlaceholderText(trUtf8(std::to_string(cl.getPassportNum()).c_str()));
    std::string d = this->clientManager.fromINTtoDate(cl.getBirthDate());
    QString s = trUtf8(d.c_str());
    QDate date = QDate::fromString(s, "dd.MM.yyyy");
    std::cout << d;
    this->ui->dateEdit->setDate(date);
}

UpdateClientWindow::~UpdateClientWindow()
{
    delete ui;
}

void UpdateClientWindow::on_enter_clicked()
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
    long int p_num;
    if (passport.empty())
        p_num = NONE;
    else
        p_num = std::stol(passport);
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
        this->clientManager.changeClientInfo(this->client_id, inf);
    }
    catch (const std::exception &e)
    {
        messageBox.critical(0, "Error", e.what());
        messageBox.setFixedSize(500,200);
        return;
    }
    this->logger->log(INFO, "Updated client success");
    messageBox.information(0, "Успех!", "Удалось успешно обновить данные!");
    this->close();
    ClientWindow *w = new ClientWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                       this->bankManager, this->requestManager, *this->logger, this->client_id);
    w->show();
}

void UpdateClientWindow::on_back_clicked()
{
    this->close();
    ClientWindow *w = new ClientWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                       this->bankManager, this->requestManager, *this->logger, this->client_id);
    w->show();
}

void UpdateClientWindow::on_change_password_clicked()
{
    QMessageBox messageBox;
    std::string password_old = this->ui->passwdEdit->text().toStdString();
    std::string password_new = this->ui->passwd2Edit->text().toStdString();
    if ((password_old.empty()) || (password_new.empty()))
    {
        messageBox.critical(0, "Ошибка!", "Все поля должны быть заполнены!");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        try
        {
            Client cl = this->clientManager.viewClient(this->client_id);
            User usr = this->authManager.viewUser(cl.getUserID());
            if (usr.getPassword() != password_old)
            {
                messageBox.critical(0, "Ошибка!", "Введен неверный старый пароль!");
                messageBox.setFixedSize(500,200);
                return;
            }
            this->authManager.changePassword(cl.getUserID(), password_new);
            this->logger->log(INFO, "Client changed password success");
            messageBox.information(0, "Успех!", "Пароль успешно изменен!");
            messageBox.setFixedSize(500,200);
            this->close();
            MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                       this->bankManager, this->requestManager, *this->logger);
            w->show();
        }
        catch (const std::exception &e)
        {
                messageBox.critical(0, "Ошибка!", e.what());
                messageBox.setFixedSize(500,200);
                this->logger->log(ERROR, e.what());
        }
    }
}
