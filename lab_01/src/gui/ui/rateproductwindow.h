#ifndef RATEPRODUCTWINDOW_H
#define RATEPRODUCTWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMessageBox>
#include <fstream>
#include <cmath>
#include "../auth_manager/GuiAuthManager.h"
#include "../managers_manager/GuiManagersManager.h"
#include "../client_manager/GuiClientManager.h"
#include "../product_manager/GuiProductManager.h"
#include "../bank_manager/GuiBankManager.h"
#include "../request_manager/GuiRequestManager.h"
#include "../../business_logic/rules/ILogger.h"

namespace Ui {
class RateProductWindow;
}

class RateProductWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RateProductWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                               GUIClientManager &clientmanager, GUIProductManager &productmanager,
                               GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int client_id, int req_id, QWidget *parent = nullptr);
    ~RateProductWindow();

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();

private:
    Ui::RateProductWindow *ui;
    GUIAuthManager authManager;
    GUIManagersManager managerManager;
    GUIClientManager clientManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
    int client_id;
    int request_id;
};

#endif // RATEPRODUCTWINDOW_H
