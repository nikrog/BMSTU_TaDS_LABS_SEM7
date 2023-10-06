#include "updateproductwindow.h"
#include "ui_updateproductwindow.h"
#include "managerwindow.h"

UpdateProductWindow::UpdateProductWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager, GUIProductManager &productmanager,
                                         GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int man_id, int prod_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateProductWindow)
{
    ui->setupUi(this);
    this->clientManager = clientmanager;
    this->authManager = authmanager;
    this->managerManager = managersmanager;
    this->productManager = productmanager;
    this->bankManager = bankmanager;
    this->requestManager = requestmanager;
    this->logger = &logger;
    this->manager_id = man_id;
    this->product_id = prod_id;
    Product prod = this->productManager.viewProduct(this->product_id);
    this->ui->nameEdit->setPlaceholderText(trUtf8(prod.getName().c_str()));
    this->ui->rate->setValue(prod.getRate());
    this->ui->min_sum->setValue(prod.getMinSum());
    this->ui->max_sum->setValue(prod.getMaxSum());
    this->ui->min_time->setValue(prod.getMinTime());
    this->ui->max_time->setValue(prod.getMaxTime());
    this->ui->prod_type->setValue(prod.getType());
    std::vector<std::string> cur = {"Рубль", "Доллар", "Евро", "Юань"};
    size_t ind = prod.getCurrency();
    ui->cur_type->addItem(trUtf8(cur[ind].c_str()));
    for (size_t i = 0; i < cur.size(); i++)
    {
        if (i != ind)
            ui->cur_type->addItem(trUtf8(cur[i].c_str()));
    }
}

UpdateProductWindow::~UpdateProductWindow()
{
    delete ui;
}

void UpdateProductWindow::on_enter_clicked()
{
    QMessageBox messageBox;
    ProductInfo inf;
    Manager m = this->managerManager.viewManager(this->manager_id);
    std::vector<std::string> cur = {"Рубль", "Доллар", "Евро", "Юань"};
    std::string name = this->ui->nameEdit->text().toStdString();
    std::string currency = this->ui->cur_type->currentText().toStdString();
    Curtype i_cur = ROUBLE;
    for (size_t i = 0; i < cur.size(); i++)
    {
        if (cur[i] == currency)
            i_cur = (Curtype) i;
    }
    float min_sum = this->ui->min_sum->value();
    float max_sum = this->ui->max_sum->value();
    float min_time = this->ui->min_time->value();
    float max_time = this->ui->max_time->value();
    float rate = this->ui->rate->value();
    Prodtype t = (Prodtype) this->ui->prod_type->value();
    inf.name = name;
    inf.min_sum = min_sum;
    inf.max_sum = max_sum;
    inf.min_time = min_time;
    inf.max_time = max_time;
    inf.currency = i_cur;
    inf.type = t;
    inf.count_rating = 0;
    inf.sum_rating = 0;
    inf.bank_id = m.getBankID();
    inf.rate = rate;
    try
    {
        this->productManager.changeProduct(this->product_id, inf);
        this->logger->log(INFO, "Manager updated product");
        messageBox.information(0, "Успех!", "Банковский продукт успешно обновлен!");
        this->close();
        ManagerWindow *w = new ManagerWindow(this->authManager, this->managerManager, this->clientManager,
                                                           this->productManager, this->bankManager, this->requestManager, *this->logger, this->manager_id);
        w->show();
    }
    catch (const std::exception &e)
    {
        messageBox.critical(0, "Ошибка!", e.what());
        messageBox.setFixedSize(500,200);
        return;
    }
}

void UpdateProductWindow::on_back_clicked()
{
    this->close();
    ManagerWindow *w = new ManagerWindow(this->authManager, this->managerManager, this->clientManager,
                                                       this->productManager, this->bankManager, this->requestManager, *this->logger, this->manager_id);
    w->show();
}
