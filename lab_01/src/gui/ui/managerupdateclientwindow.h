#ifndef MANAGERUPDATECLIENTWINDOW_H
#define MANAGERUPDATECLIENTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "../auth_manager/GuiAuthManager.h"
#include "../managers_manager/GuiManagersManager.h"
#include "../client_manager/GuiClientManager.h"
#include "../product_manager/GuiProductManager.h"
#include "../bank_manager/GuiBankManager.h"
#include "../request_manager/GuiRequestManager.h"
#include "../../business_logic/rules/ILogger.h"

namespace Ui {
class ManagerUpdateClientWindow;
}

class ManagerUpdateClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerUpdateClientWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager,
                                       GUIProductManager &productmanager, GUIBankManager &bankmanager, GUIRequestManager &requestmanager,
                                       ILogger &logger, int cl_id, int m_id, QWidget *parent = nullptr);
    ~ManagerUpdateClientWindow();

private slots:
    void on_enter_clicked();
    void on_back_clicked();

private:
    Ui::ManagerUpdateClientWindow *ui;
    GUIAuthManager authManager;
    GUIClientManager clientManager;
    GUIManagersManager managerManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
    int client_id;
    int manager_id;
};

#endif // MANAGERUPDATECLIENTWINDOW_H
