#include "rateproductwindow.h"
#include "ui_rateproductwindow.h"

RateProductWindow::RateProductWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                                     GUIClientManager &clientmanager, GUIProductManager &productmanager,
                                     GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int cl_id, int req_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RateProductWindow)
{
    ui->setupUi(this);
    this->authManager = authmanager;
    this->managerManager = managermanager;
    this->clientManager = clientmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->client_id = cl_id;
    this->request_id = req_id;
    Request r = this->requestManager.viewRequest(this->request_id);
    Product p = this->productManager.viewProduct(r.getProductID());
    this->ui->nameEdit->setPlaceholderText(trUtf8(p.getName().c_str()));
}

RateProductWindow::~RateProductWindow()
{
    delete ui;
}

void RateProductWindow::on_cancel_clicked()
{
    this->close();
}


void RateProductWindow::on_ok_clicked()
{
    QMessageBox messageBox;
    int score = this->ui->score->value();
    Client cl = this->clientManager.viewClient(this->client_id);
    try
    {
        this->requestManager.rateProduct(this->request_id, cl.getUserID(), score);
        messageBox.information(0, "Успех!", "Продукт оценен успешно!");
        messageBox.setFixedSize(500,200);
    }
    catch (const std::exception &e)
    {
        this->logger->log(ERROR, std::string("Error: ") + e.what());
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
    }
    this->close();
}
