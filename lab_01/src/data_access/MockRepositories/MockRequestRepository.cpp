#include "MockRequestRepository.h"

MockRequestRepository::~MockRequestRepository()
{}

Request MockRequestRepository::getRequestByID(int id)
{
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getID() == id)
            return tmpRequest;
    }
    
    return Request();
}

std::vector<Request> MockRequestRepository::getRequestByState(State_t state)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getState() == state)
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getRequestByDate(date_t date)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getDate() == date)
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getRequestByClient(int client_id)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getClientID() == client_id)
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getRequestByManager(int manager_id)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getManagerID() == manager_id)
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getRequestBySum(float min_sum, float max_sum)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if ((tmpRequest.getSum() >= min_sum) && (tmpRequest.getSum() <= max_sum))
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getRequestByDuration(int min_time, int max_time)
{
    std::vector<Request> res_requests;
    for (Request tmpRequest : this->requests)
    {
        if ((tmpRequest.getDuration() >= min_time) && (tmpRequest.getDuration() <= max_time))
            res_requests.push_back(tmpRequest);
    }
    
    return res_requests;
}
std::vector<Request> MockRequestRepository::getAllRequests()
{
    return this->requests;
}
int MockRequestRepository::addRequest(RequestInfo inf)
{
    int N = this->requests.size();
    Request tmpRequest = Request(N + 1, inf.client_id, inf.product_id, inf.manager_id,
     inf.sum, inf.duration, inf.date, inf.state);
    this->requests.push_back(tmpRequest);
    return N + 1;
}
void MockRequestRepository::deleteEl(int id)
{
    std::vector<Request> new_requests;
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getID() != id)
            new_requests.push_back(tmpRequest);
    }
    this->requests = new_requests;
}
void MockRequestRepository::updateEl(Request req_el)
{
    for (Request tmpRequest : this->requests)
    {
        if (tmpRequest.getID() == req_el.getID())
        {
            this->requests[tmpRequest.getID() - 1].setSum(req_el.getSum());
            this->requests[tmpRequest.getID() - 1].setDuration(req_el.getDuration());
            this->requests[tmpRequest.getID() - 1].setDate(req_el.getDate());
            this->requests[tmpRequest.getID() - 1].setManagerID(req_el.getManagerID());
            this->requests[tmpRequest.getID() - 1].setState(req_el.getState());
        }
    }
    return;
}