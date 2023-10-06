#ifndef USERWINDOW_H
#define USERWINDOW_H

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
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                        GUIClientManager &clientmanager, GUIProductManager &productmanager,
                        GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_search_clicked();
    void on_auth_clicked();
    //void handleClick();

private:
    Ui::UserWindow *ui;
    GUIAuthManager authManager;
    GUIManagersManager managerManager;
    GUIClientManager clientManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
};

#endif // USERWINDOW_H
