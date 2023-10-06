#ifndef REGISTERCLIENTWINDOW_H
#define REGISTERCLIENTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "../auth_manager/GuiAuthManager.h"
#include "../managers_manager/GuiManagersManager.h"
#include "../client_manager/GuiClientManager.h"
#include "../product_manager/GuiProductManager.h"
#include "../bank_manager/GuiBankManager.h"
#include "../request_manager/GuiRequestManager.h"
#include "../../business_logic/rules/ILogger.h"
#include "registerclient2window.h"

namespace Ui {
class RegisterClientWindow;
}

class RegisterClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterClientWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager,
                                  GUIProductManager &productmanager, GUIBankManager &bankmanager, GUIRequestManager &requestmanager,
                                  ILogger &logger, QWidget *parent = nullptr);
    ~RegisterClientWindow();

private slots:
    void on_enter_clicked();
    void on_back_clicked();

private:
    Ui::RegisterClientWindow *ui;
    GUIAuthManager authManager;
    GUIClientManager clientManager;
    GUIManagersManager managerManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
};

#endif // REGISTERCLIENTWINDOW_H
