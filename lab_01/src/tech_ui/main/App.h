#ifndef PPO_APP_H
#define PPO_APP_H

#include "Printer.h"
#include "AuthStates.h"
#include "Commands.h"

#include "../../business_logic/rules/UserRules.h"
#include "../../business_logic/rules/ClientRules.h"
#include "../../business_logic/rules/BankRules.h"
#include "../../business_logic/rules/ManagerRules.h"
#include "../../business_logic/rules/ProductRules.h"
#include "../../business_logic/rules/RequestRules.h"

#include "../../business_logic/models/ModelUser.h"
#include "../auth_manager/AuthManager.h"
#include "../product_manager/ProductManager.h"
#include "../request_manager/RequestManager.h"
#include "../client_manager/ClientManager.h"
#include "../bank_manager/BankManager.h"
#include "../managers_manager/ManagersManager.h"

#include "../../data_access/PostgresRepositories/PgUserRepository.h"
#include "../../data_access/PostgresRepositories/PgBankRepository.h"
#include "../../data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../data_access/PostgresRepositories/PgClientRepository.h"
#include "../../data_access/PostgresRepositories/PgProductRepository.h"
#include "../../data_access/PostgresRepositories/PgRequestRepository.h"
#include "../../config/ConfigManager.h"
#include "../../business_logic/rules/ILogger.h"
#include "../../logger/Logger.h"

class App {
private:
    AppPrinter printer;
    AuthStates app_state;
    CommandHandler cmd_handler;
    CMD_KEYS getCommandKey(std::string cmd);
    AuthManager authManager;
    ClientManager clientManager;
    BankManager bankManager;
    ManagersManager managersManager;
    ProductManager productManager;
    RequestManager requestManager;
    ILogger *logger;

    int user_id;
    int client_id;
    int manager_id;
    void handleCommand(CMD_KEYS key);
public:
    App(AuthManager &authManager, ClientManager &clientManager, BankManager &bankManager,
    ManagersManager &managersManager, ProductManager &productManager, RequestManager &requestManager,
    ILogger &logger);
    ~App() = default;
    void menu();
};


#endif //PPO_APP_H
