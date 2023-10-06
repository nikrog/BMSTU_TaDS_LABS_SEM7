#include "App.h"

App::App(AuthManager &authManager, ClientManager &clientManager, BankManager &bankManager,
        ManagersManager &managersManager, ProductManager &productManager, RequestManager &requestManager, ILogger &logger)
{
    this->printer = AppPrinter();
    this->cmd_handler = CommandHandler();
    this->app_state = AuthStates();
    this->user_id = NONE;
    this->client_id = NONE;
    this->manager_id = NONE;
    this->authManager = authManager;
    this->clientManager = clientManager;
    this->bankManager = bankManager;
    this->managersManager = managersManager;
    this->productManager = productManager;
    this->requestManager = requestManager;
    this->logger = &logger;
}

void App::menu()
{
    this->printer.print_menu();
    std::string cmd;
    std::cin >> cmd;
    CMD_KEYS key = this->getCommandKey(cmd);
    this->handleCommand(key);
}

CMD_KEYS App::getCommandKey(std::string cmd)
{
    return this->cmd_handler.handle(cmd);
}

void App::handleCommand(CMD_KEYS key)
{
    switch (key)
    {
    case EXIT:
        this->logger->log(INFO, "App exited");
        std::exit(EXIT);

    case UN_AUTH:
        this->logger->log(INFO, "UN_AUTH command handled");
        if (!this->app_state.isUnAuth()) {
            this->app_state.toUnAuth();
            this->printer.print_unauth_success();
            this->user_id = NONE;
            this->client_id = NONE;
            this->manager_id = NONE;
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;

    case AUTH:
        this->logger->log(INFO, "AUTH command handled");
        if (this->app_state.isUnAuth())
        {
            Roles role = this->authManager.tryToAuthorize();
            switch (role) {
            case CLIENT:
            {
                this->app_state.toClientAuth();
                int userID = this->authManager.getUserID(this->authManager.getLogin());
                this->user_id = userID;
                this->client_id = this->clientManager.getClientByUserID(userID);
                break;
            }
            case MANAGER:
            {
                this->app_state.toManagerAuth();
                int userID = this->authManager.getUserID(this->authManager.getLogin());
                this->user_id = userID;
                this->manager_id = this->managersManager.getManagerByUserID(userID);
                break;
            }
            case ADMIN:
            {
                this->app_state.toAdminAuth();
                int userID = this->authManager.getUserID(this->authManager.getLogin());
                this->user_id = userID;
                break;
            }
            default:
                break;
            }
        };
        break;

    case ADD_CLIENT:
        this->logger->log(INFO, "ADD_CLIENT command handled");
        if ((this->app_state.isUnAuth()) || (this->app_state.isAdminAuth()))
        {
            this->clientManager.addClient();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case ADD_MANAGER:
        this->logger->log(INFO, "ADD_MANAGER command handled");
        if (this->app_state.isAdminAuth())
        {
            this->managersManager.addManager();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case VIEW_CLIENT:
        this->logger->log(INFO, "VIEW_CLIENT command handled");
        if (this->app_state.isManagerAuth())
        {
            this->clientManager.viewClient();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case VIEW_ALL_CLIENTS:
        this->logger->log(INFO, "VIEW_ALL_CLIENTS command handled");
        if (this->app_state.isManagerAuth())
        {
            this->clientManager.viewAllClients();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case ADD_PRODUCT:
        this->logger->log(INFO, "ADD_PRODUCT command handled");
        if ((this->app_state.isManagerAuth()) || (this->app_state.isAdminAuth()))
        {
            this->productManager.addProduct();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case VIEW_ALL_PRODUCTS:
        this->logger->log(INFO, "VIEW_ALL_PRODUCTS command handled");
        this->productManager.viewAllProducts();
        break;
    case VIEW_ALL_REQUESTS:
        this->logger->log(INFO, "VIEW_ALL_REQUESTS command handled");
        if ((this->app_state.isManagerAuth()) || (this->app_state.isAdminAuth()))
        {
            this->requestManager.viewAllRequests();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case MAKE_REQUEST:
        this->logger->log(INFO, "MAKE_REQUEST command handled");
        if (this->app_state.isClientAuth())
        {
            this->requestManager.makeRequest(this->user_id, this->client_id);
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case VIEW_MY_REQUESTS:
        this->logger->log(INFO, "VIEW_MY_REQUESTS command handled");
        if (this->app_state.isClientAuth())
        {
            this->requestManager.viewMyRequests(this->client_id);
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case CONFIRM_REQUEST:
        this->logger->log(INFO, "CONFIRM_REQUEST command handled");
        if (this->app_state.isManagerAuth())
        {
            this->requestManager.confirmRequest(this->manager_id);
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case REJECT_REQUEST:
        this->logger->log(INFO, "REJECT_REQUEST command handled");
        if (this->app_state.isManagerAuth())
        {
            this->requestManager.rejectRequest(this->manager_id);
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case RATE_PRODUCT:
        this->logger->log(INFO, "RATE_PRODUCT command handled");
        if (this->app_state.isClientAuth())
        {
            this->requestManager.rateProduct(this->user_id);
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case VIEW_ALL_BANKS:
        this->logger->log(INFO, "VIEW_ALL_BANKS command handled");
        this->bankManager.printAllBanks();
        break;
    case UPDATE_PRODUCT:
        this->logger->log(INFO, "UPDATE_PRODUCT command handled");
        if ((this->app_state.isManagerAuth()) || (this->app_state.isAdminAuth()))
        {
            this->productManager.changeProduct();
        }
        else {
            this->printer.print_not_role();
            this->logger->log(WARNING, "Failed access attempt to command");
        }
        break;
    case NOT_A_COMMAND:
        this->logger->log(WARNING, "Not existent command handled");
        this->printer.print_not_a_command();
    }
}
