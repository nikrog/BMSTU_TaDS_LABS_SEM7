#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

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
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                          GUIClientManager &clientmanager, GUIProductManager &productmanager,
                          GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int client_id, QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_search_clicked();
    void on_exit_clicked();
    void on_make_request_clicked();
    void on_score_clicked();
    void on_delete_client_clicked();
    void on_update_client_clicked();
    void onMakeReqBtnClicked();
    void onRateBtnClicked();
    QWidget *createButtonWidget(char * name) const;
    QWidget *createRateButtonWidget(char * name, bool enable) const;

private:
    Ui::ClientWindow *ui;
    GUIAuthManager authManager;
    GUIManagersManager managerManager;
    GUIClientManager clientManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
    int client_id;
};

#endif // CLIENTWINDOW_H
