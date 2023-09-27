#ifndef UPDATEBANKWINDOW_H
#define UPDATEBANKWINDOW_H

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
class UpdateBankWindow;
}

class UpdateBankWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateBankWindow(GUIAuthManager &authmanager, GUIClientManager &clientmanager, GUIManagersManager &managersmanager,
                              GUIProductManager &productmanager, GUIBankManager &bankmanager, GUIRequestManager &requestmanager,
                              ILogger &logger, int user_id, int bank_id, QWidget *parent = nullptr);
    ~UpdateBankWindow();

private slots:
    void on_enter_clicked();
    void on_back_clicked();

private:
    Ui::UpdateBankWindow *ui;
    GUIAuthManager authManager;
    GUIClientManager clientManager;
    GUIManagersManager managerManager;
    GUIProductManager productManager;
    GUIBankManager bankManager;
    GUIRequestManager requestManager;
    ILogger *logger;
    int user_id;
    int bank_id;
};

#endif // UPDATEBANKWINDOW_H
