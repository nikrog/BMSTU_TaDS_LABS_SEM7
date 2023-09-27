#ifndef PPO_REQUESTMANAGER_H
#define PPO_REQUESTMANAGER_H

#include "RequestGetter.h"
#include "RequestPrinter.h"
#include "../../business_logic/rules/RequestRules.h"

class RequestManager {
private:
    RequestRules requestController;
    RequestPrinter printer;
    RequestGetter getter;

public:
    RequestManager(RequestRules &rController);
    RequestManager();
    ~RequestManager() = default;
    void viewAllRequests();
    void viewMyRequests(int client_id);
    void makeRequest(int user_id, int client_id);
    void rejectRequest(int manager_id);
    void confirmRequest(int manager_id);
    void rateProduct(int user_id);
    void changeRequest();
};


#endif //PPO_REQUESTMANAGER_H
