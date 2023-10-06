#include "registerclientwindow.h"
#include "ui_registerclientwindow.h"
#include "mainwindow.h"

RegisterClientWindow::RegisterClientWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager,
                                           GUIProductManager &productmanager, GUIBankManager &bankmanager, GUIRequestManager &requestmanager,
                                           ILogger &logger, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterClientWindow)
{
    ui->setupUi(this);
    this->clientManager = clientmanager;
    this->authManager = authmanager;
    this->managerManager = managersmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
}

RegisterClientWindow::~RegisterClientWindow()
{
    delete ui;
}

void RegisterClientWindow::on_enter_clicked()
{
    QMessageBox messageBox;
    std::string login = this->ui->loginEdit->text().toStdString();
    std::string password = this->ui->passwdEdit->text().toStdString();
    std::string password_rep = this->ui->passwd2Edit->text().toStdString();
    if ((login.empty()) || (password.empty()) || (password_rep.empty()))
    {
        messageBox.critical(0, "Error", "Все поля должны быть заполнены!");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        try
        {
            int u_id = this->authManager.getUserID(login);
            if (u_id != NONE)
            {
                messageBox.critical(0, "Error", "Данный логин занят! Введите другой!");
                messageBox.setFixedSize(500,200);
            }
        }
        catch (const std::exception &e)
        {
            if (password != password_rep)
            {
                messageBox.critical(0, "Error", "Пароли не совпадают!");
                messageBox.setFixedSize(500,200);
            }
            else
            {
                this->logger->log(INFO, "Register new user attempt");
                this->close();
                RegisterClient2Window *w = new RegisterClient2Window(this->authManager, this->clientManager, this->managerManager, this->productManager,
                                                                     this->bankManager, this->requestManager, *this->logger, login, password);
                w->show();
            }
        }
    }
}

void RegisterClientWindow::on_back_clicked()
{
    this->close();
    MainWindow *w = new MainWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
    w->show();
}
