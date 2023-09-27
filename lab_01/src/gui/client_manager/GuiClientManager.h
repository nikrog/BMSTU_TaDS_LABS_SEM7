#ifndef PPO_GUICLIENTMANAGER_H
#define PPO_GUICLIENTMANAGER_H

#include "../../business_logic/rules/ClientRules.h"
#include "../../business_logic/rules/UserRules.h"

class GUIClientManager {
private:
    ClientRules clientController;
    UserRules userController;
public:
    GUIClientManager(ClientRules &cController, UserRules &uController);
    GUIClientManager();
    ~GUIClientManager() = default;
    void addClient(ClientInfo inf, std::string login, std::string password);
    Client viewClient(int id);
    std::vector<Client> viewAllClients();
    void changeClientInfo(int id, ClientInfo inf);
    int getClientByUserID(int user_id);
    int fromDateToINT(std::string year, std::string month, std::string day);
    std::string fromINTtoDate(int i_date);
};


#endif //PPO_GUICLIENTMANAGER_H
