#include "managerupdateclientwindow.h"
#include "ui_managerupdateclientwindow.h"
#include "managerwindow.h"

ManagerUpdateClientWindow::ManagerUpdateClientWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                                       GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int cl_id, int m_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerUpdateClientWindow)
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
    this->manager_id = m_id;
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

ManagerUpdateClientWindow::~ManagerUpdateClientWindow()
{
    delete ui;
}

void ManagerUpdateClientWindow::on_enter_clicked()
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
    ManagerWindow *w = new ManagerWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                       this->bankManager, this->requestManager, *this->logger, this->manager_id);
    w->show();
}

void ManagerUpdateClientWindow::on_back_clicked()
{
    this->close();
    ManagerWindow *w = new ManagerWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                       this->bankManager, this->requestManager, *this->logger, this->manager_id);
    w->show();
}
