#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

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

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(GUIAuthManager &authmanager, GUIManagersManager &managermanager,
                         GUIClientManager &clientmanager, GUIProductManager &productmanager,
                         GUIBankManager &bankmanager, GUIRequestManager &requestmanager, ILogger &logger, int u_id, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_search_clicked();
    void on_exit_clicked();
    void on_add_manager_clicked();
    void on_update_manager_clicked();
    void on_delete_user_clicked();
    void on_update_user_clicked();
    void on_delete_bank_clicked();
    void on_update_password_clicked();
    void on_add_bank_clicked();
    void on_update_bank_clicked();
    void onDeleteUserBtnClicked();
    void onDeleteBankBtnClicked();
    void onUpdateBankBtnClicked();
    QWidget *createDeleteUserButtonWidget(char *name, bool enable) const;
    QWidget *createDeleteBankButtonWidget(char *name) const;
    QWidget *createUpdateBankButtonWidget(char *name) const;

private:
    Ui::AdminWindow *ui;
    GUIAuthManager authManager;
    GUIManagersManager managerManager;
    GUIClientManager clientManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
    int user_id;
};

#endif // ADMINWINDOW_H
