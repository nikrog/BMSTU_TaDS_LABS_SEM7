#include "changepasswordwindow.h"
#include "ui_changepasswordwindow.h"
#include "mainwindow.h"

ChangePasswordWindow::ChangePasswordWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager,
                                           GUIProductManager &productmanager, GUIBankManager &bankmanager, GUIRequestManager &requestmanager,
                                           ILogger &logger, int u_id, int m_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangePasswordWindow)
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
    this->manager_id = m_id;
}

ChangePasswordWindow::~ChangePasswordWindow()
{
    delete ui;
}

void ChangePasswordWindow::on_enter_clicked()
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
            User usr = this->authManager.viewUser(this->user_id);
            if (usr.getPassword() != password_old)
            {
                messageBox.critical(0, "Ошибка!", "Введен неверный старый пароль!");
                messageBox.setFixedSize(500,200);
                return;
            }
            this->authManager.changePassword(this->user_id, password_new);
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

void ChangePasswordWindow::on_back_clicked()
{
    this->close();
    if (this->manager_id == NONE)
    {
        AdminWindow *w = new AdminWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger, this->user_id);
        w->show();
    }
    else
    {
        ManagerWindow *w = new ManagerWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                             this->bankManager, this->requestManager, *this->logger, this->manager_id);
        w->show();
    }

}
