#include "App.h"

int main()
{
    ConfigManager config_manager;
    std::string DB = config_manager.getDB();
    ConnectionParams connectParams = config_manager.getParams();
    
    std::vector<int> p = config_manager.getBLparams();
    LogLevel lvl = config_manager.getLogLevel();
    std::string log_file = config_manager.getLogFile();
    //std::cout << log_file;
    Logger logger = Logger(log_file, lvl);
    logger.log(INFO, "App started");
    //ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    if (DB == "postgres")
    {
        PgUserRepository userRepo = PgUserRepository(connectParams);
        PgBankRepository bankRepo = PgBankRepository(connectParams);
        PgManagerRepository managerRepo = PgManagerRepository(connectParams);
        PgClientRepository clientRepo = PgClientRepository(connectParams);
        PgProductRepository productRepo = PgProductRepository(connectParams);
        PgRequestRepository requestRepo = PgRequestRepository(connectParams); 

        UserRules urules = UserRules(userRepo, logger, p[1], p[0]);
        BankRules brules = BankRules(bankRepo, logger);
        ManagerRules mrules = ManagerRules(managerRepo, bankRepo, userRepo, clientRepo, logger);
        ClientRules crules = ClientRules(clientRepo, userRepo, managerRepo, logger);
        ProductRules prules = ProductRules(productRepo, bankRepo, logger);
        RequestRules rrules = RequestRules(requestRepo, clientRepo, managerRepo, productRepo, userRepo, logger);

        AuthManager authManager = AuthManager(urules);
        ClientManager clManager = ClientManager(crules, urules);
        ManagersManager manManager = ManagersManager(mrules, urules);
        BankManager bankManager = BankManager(brules);
        ProductManager prodManager = ProductManager(prules);
        RequestManager reqManager = RequestManager(rrules);

        App app = App(authManager, clManager, bankManager, manManager, prodManager, reqManager, logger);

        for (;;)
            app.menu();
    }
}