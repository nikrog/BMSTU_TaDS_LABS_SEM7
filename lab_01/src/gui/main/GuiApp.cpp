#include "GuiApp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigManager config_manager;
    std::string DB = config_manager.getDB();
    ConnectionParams connectParams = config_manager.getParams();
    std::vector<int> p = config_manager.getBLparams();
    LogLevel lvl = config_manager.getLogLevel();
    std::string log_file = config_manager.getLogFile();
    Logger logger = Logger(log_file, lvl);
    logger.log(INFO, "App started");

    if (DB == "postgres")
    {
        logger.log(INFO, "Postgres DB connected");
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

        GUIAuthManager authManager = GUIAuthManager(urules);
        GUIClientManager clManager = GUIClientManager(crules, urules);
        GUIManagersManager manManager = GUIManagersManager(mrules, urules);
        GUIBankManager bankManager = GUIBankManager(brules);
        GUIProductManager prodManager = GUIProductManager(prules);
        GUIRequestManager reqManager = GUIRequestManager(rrules, prules);
        MainWindow w(authManager, manManager, clManager, prodManager, bankManager, reqManager, logger);
        w.show();
        return a.exec();
    }
    else
    {
        logger.log(ERROR, "Unknown DB");
    }
}
