#ifndef PPO_GUIREQUESTMANAGER_H
#define PPO_GUIREQUESTMANAGER_H

#include "../../business_logic/rules/RequestRules.h"
#include "../../business_logic/rules/ProductRules.h"

class GUIRequestManager {
private:
    RequestRules requestController;
    ProductRules productController;

public:
    GUIRequestManager(RequestRules &rController, ProductRules &pcontroller);
    GUIRequestManager();
    ~GUIRequestManager() = default;
    std::vector<Request> viewAllRequests();
    std::vector<Request> viewMyRequests(int client_id);
    std::vector<Request> viewBankRequests(int bank_id);
    Request viewRequest(int req_id);
    void makeRequest(int user_id, RequestInfo inf);
    void rejectRequest(int req_id,int manager_id);
    void confirmRequest(int req_id, int manager_id);
    void rateProduct(int req_id, int user_id, int score);
    void changeRequest(int id, RequestInfo inf);
};


#endif //PPO_GUIREQUESTMANAGER_H
