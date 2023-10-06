#include "GuiRequestManager.h"

GUIRequestManager::GUIRequestManager(RequestRules &rController, ProductRules &pController)
{
    this->requestController = rController;
    this->productController = pController;
}

GUIRequestManager::GUIRequestManager(){}

std::vector<Request> GUIRequestManager::viewAllRequests()
{
    std::vector<Request> requests = this->requestController.getAllRequests();
    return requests;
}

Request GUIRequestManager::viewRequest(int req_id)
{
    Request r = this->requestController.getRequest(req_id);
    return r;
}

std::vector<Request> GUIRequestManager::viewMyRequests(int client_id)
{
    std::vector<Request> requests = this->requestController.getAllRequests();
    std::vector<Request> my_requests = std::vector<Request>();
    for (size_t i = 0; i < requests.size(); i++)
    {
        if (requests[i].getClientID() == client_id)
        {
            my_requests.push_back(requests[i]);
        }
    }
    return my_requests;
}

std::vector<Request> GUIRequestManager::viewBankRequests(int bank_id)
{
    std::vector<Request> requests = this->requestController.getAllRequests();
    std::vector<Request> bank_requests = std::vector<Request>();
    for (size_t i = 0; i < requests.size(); i++)
    {
        Product prod = this->productController.getProduct(requests[i].getProductID());
        if (prod.getBankID() == bank_id)
        {
            bank_requests.push_back(requests[i]);
        }
    }
    return bank_requests;
}

void GUIRequestManager::makeRequest(int user_id, RequestInfo inf)
{
    int id = this->requestController.makeRequest(user_id, inf);
    Request req = this->requestController.getRequest(id);
    if (req.getID() == NONE)
    {
        throw RequestAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

void GUIRequestManager::changeRequest(int id, RequestInfo inf)
{
    Request tmpRequest = this->requestController.getRequest(id);
    if (tmpRequest.getID() != NONE)
    {
        if (inf.sum > 0)
        {
            tmpRequest.setSum(inf.sum);
        }
        
        if (inf.duration > 0)
        {
            tmpRequest.setDuration(inf.duration);
        }

        this->requestController.updateRequest(tmpRequest);
    }
}

void GUIRequestManager::rejectRequest(int req_id, int manager_id)
{
    Request tmpRequest = this->requestController.getRequest(req_id);
    if (tmpRequest.getID() != NONE)
    {

        this->requestController.rejectRequest(req_id, manager_id);
    }
}

void GUIRequestManager::confirmRequest(int req_id, int manager_id)
{
    Request tmpRequest = this->requestController.getRequest(req_id);
    if (tmpRequest.getID() != NONE)
    {
        this->requestController.confirmRequest(req_id, manager_id);
    }
}

void GUIRequestManager::rateProduct(int req_id, int user_id, int score)
{
    Request tmpRequest = this->requestController.getRequest(req_id);
    if (tmpRequest.getID() != NONE)
    {
        this->requestController.rateProduct(req_id, user_id, score);
    }
}
