#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMessageBox>
#include <fstream>
#include "../auth_manager/GuiAuthManager.h"
#include "../managers_manager/GuiManagersManager.h"
#include "../client_manager/GuiClientManager.h"
#include "../product_manager/GuiProductManager.h"
#include "../bank_manager/GuiBankManager.h"
#include "../request_manager/GuiRequestManager.h"
#include "../../business_logic/rules/ILogger.h"
#include "clientwindow.h"
#include "adminwindow.h"
#include "managerwindow.h"
#include "userwindow.h"
#include "registerclientwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
             class ClientWindow;
             class ManagerWindow;
             class AdminWindow;
             class UserWindow;
             class RegisterClientWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                   GUIClientManager &clientmanager, GUIProductManager &productmanager,
                   GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    Roles on_enter_clicked();
    void on_notauth_clicked();
    void on_registration_clicked();

private:
    Ui::MainWindow *ui;
    GUIAuthManager authManager;
    GUIManagersManager managerManager;
    GUIClientManager clientManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
};

#endif // MAINWINDOW_H
