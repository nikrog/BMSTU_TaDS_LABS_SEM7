#ifndef PPO_CLIENTMANAGER_H
#define PPO_CLIENTMANAGER_H

#include "ClientGetter.h"
#include "ClientPrinter.h"
#include "../../business_logic/rules/ClientRules.h"
#include "../../business_logic/rules/UserRules.h"

class ClientManager {
private:
    ClientGetter getter;
    ClientPrinter printer;
    ClientRules clientController;
    UserRules userController;
public:
    ClientManager(ClientRules &cController, UserRules &uController);
    ClientManager();
    ~ClientManager() = default;
    void addClient();
    void viewClient();
    void viewAllClients();
    void changeClientInfo();
    int getClientByUserID(int user_id);
};


#endif //PPO_CLIENTMANAGER_H
