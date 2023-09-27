#include "makerequestwindow.h"
#include "ui_makerequestwindow.h"

MakeRequestWindow::MakeRequestWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                                     GUIClientManager &clientmanager, GUIProductManager &productmanager,
                                     GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int cl_id, int prod_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MakeRequestWindow)
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
    this->product_id = prod_id;
    Product p = this->productManager.viewProduct(this->product_id);
    this->ui->nameEdit->setPlaceholderText(trUtf8(p.getName().c_str()));
}

MakeRequestWindow::~MakeRequestWindow()
{
    delete ui;
}

void MakeRequestWindow::on_cancel_clicked()
{
    this->close();
}


void MakeRequestWindow::on_ok_clicked()
{
    QMessageBox messageBox;
    RequestInfo inf;
    float sum = this->ui->sum->value();
    float dur = this->ui->duration->value();
    Client cl = this->clientManager.viewClient(this->client_id);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", now);
    std::string date(buffer);
    inf.client_id = this->client_id;
    inf.product_id = this->product_id;
    inf.sum = sum;
    inf.duration = dur;
    inf.date = date;
    inf.manager_id = NONE;
    inf.state = OPENED;
    try
    {
        this->requestManager.makeRequest(cl.getUserID(), inf);
        messageBox.information(0, "Успех!", "Заявка успешно подана!");
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
