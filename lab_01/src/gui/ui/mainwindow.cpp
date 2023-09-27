#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                       GUIClientManager &clientmanager, GUIProductManager &productmanager,
                       GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->authManager = authmanager;
    this->managerManager = managermanager;
    this->clientManager = clientmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
}

MainWindow::~MainWindow()
{
    delete ui;
}

Roles MainWindow::on_enter_clicked()
{
    QMessageBox messageBox;
    Roles result = NON_AUTH;
    std::string login = this->ui->loginEdit->text().toStdString();
    std::string password = this->ui->passwdEdit->text().toStdString();
    try {
        this->logger->log(INFO, "Authorization attempt");
        result = this->authManager.tryToAuthorize(login, password);
        //messageBox.information(0, "Успех!", "Удалось успешно войти в систему!");
        if (result == CLIENT)
        {
            int u_id = this->authManager.getUserID(login);
            int cl_id = this->clientManager.getClientByUserID(u_id);
            //this->authManager.setRole(CLIENT);
            this->logger->log(INFO, "Client authorized success");
            this->close();
            ClientWindow *w = new ClientWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                               this->bankManager, this->requestManager, *this->logger, cl_id);
            w->show();
        }
        else if (result == MANAGER)
        {
            int u_id = this->authManager.getUserID(login);
            int m_id = this->managerManager.getManagerByUserID(u_id);
            //this->authManager.setRole(MANAGER);
            this->logger->log(INFO, "Manager authorized success");
            this->close();
            ManagerWindow *w = new ManagerWindow(this->authManager,this->managerManager, this->clientManager,
                                                 this->productManager, this->bankManager, this->requestManager, *this->logger, m_id);
            w->show();
        }
        else if (result == ADMIN)
        {
            int u_id = this->authManager.getUserID(login);
            //this->authManager.setRole(ADMIN);
            this->logger->log(INFO, "Administrator authorized success");
            this->close();
            AdminWindow *w = new AdminWindow(this->authManager,this->managerManager, this->clientManager,
                                             this->productManager, this->bankManager, this->requestManager, *this->logger, u_id);
            w->show();
        }
    }  catch (const std::exception &e) {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Error", e.what());
        messageBox.setFixedSize(500,200);
    }
    return result;
}

void MainWindow::on_notauth_clicked()
{
    //this->authManager.setRole(NON_AUTH);
    this->logger->log(INFO, "Not authorize button clicked");
    this->close();
    UserWindow *w = new UserWindow(this->authManager, this->managerManager, this->clientManager, this->productManager,
                                   this->bankManager, this->requestManager, *this->logger);
    w->show();
}

void MainWindow::on_registration_clicked()
{
    //this->authManager.setRole(ADMIN);
    this->logger->log(INFO, "Registration of client attempt");
    this->close();
    RegisterClientWindow *w = new RegisterClientWindow(this->authManager, this->clientManager, this->managerManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger);
    w->show();
}
