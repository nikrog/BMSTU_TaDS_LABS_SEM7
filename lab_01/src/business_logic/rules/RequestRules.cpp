#include "RequestRules.h"

RequestRules::RequestRules(IRequestRepository &repository, IClientRepository &clientRepository,
                           IManagerRepository &managerRepository, IProductRepository &productRepository,
                           IUserRepository &userRepository, ILogger &logger)
{
    this->repository = &repository;
    this->clientRepository = &clientRepository;
    this->managerRepository = &managerRepository;
    this->productRepository = &productRepository;
    this->userRepository = &userRepository;
    this->logger = &logger;
}

RequestRules::RequestRules()
{}

RequestRules::~RequestRules()
{}

Request RequestRules::getRequest(int id) {
    Request tmpRequest = this->repository->getRequestByID(id);
    if (tmpRequest.getID() == NONE)
    {
        this->logger->log(ERROR, "Request not found");
        throw RequestNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get request success");
        return tmpRequest;
    }
}

std::vector<Request> RequestRules::getRequestByClient(int client_id)
{
    std::vector<Client> clients = this->clientRepository->getAllClients();
    int id = NONE;
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getID() == client_id)
            id = clients[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Request get error (client not found)");
        throw RequestGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Request> requests = this->repository->getRequestByClient(client_id);
    this->logger->log(INFO, "Get request by client success");
    return requests;

}

std::vector<Request> RequestRules::getRequestByDate(timereq_t date)
{
    std::vector<Request> requests = this->repository->getRequestByDate(date);
    this->logger->log(INFO, "Get request by date success");
    return requests;
}

std::vector<Request> RequestRules::getRequestByState(State_t s)
{
    std::vector<Request> requests = this->repository->getRequestByState(s);
    this->logger->log(INFO, "Get request by state success");
    return requests;
}

std::vector<Request> RequestRules::getRequestByManager(int manager_id)
{
    if (manager_id != NONE)
    {
        std::vector<Manager> managers = this->managerRepository->getAllManagers();
        int id = NONE;
        for (size_t i = 0; i < managers.size(); i++)
            if (managers[i].getID() == manager_id)
                id = managers[i].getID();
        if (id == NONE)
        {
            this->logger->log(ERROR, "Get request error (manager not found)");
            throw RequestGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    std::vector<Request> requests = this->repository->getRequestByManager(manager_id);
    this->logger->log(INFO, "Get request by manager success");
    return requests;
}

std::vector<Request> RequestRules::getRequestByDuration(int min_time, int max_time)
{
    if ((min_time < MIN_TIME) || (max_time < MIN_TIME) || (min_time > max_time))
    {
        this->logger->log(ERROR, "Get request error (incorrect duration)");
        throw RequestGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Request> requests = this->repository->getRequestByDuration(min_time, max_time);
    this->logger->log(INFO, "Get request by duration success");
    return requests;
}

std::vector<Request> RequestRules::getRequestBySum(float min_sum, float max_sum)
{
    if ((min_sum < MIN_SUM) || (max_sum < MIN_SUM) || (min_sum > max_sum))
    {
        this->logger->log(INFO, "Get request error (incorrect sum)");
        throw RequestGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Request> requests = this->repository->getRequestBySum(min_sum, max_sum);
    this->logger->log(INFO, "Get request by sum success");
    return requests;
}

int RequestRules::makeRequest(int user_id, RequestInfo inf)
{
    User tmpUser = this->userRepository->getUserByID(user_id);
    if (tmpUser.getUserRole() != CLIENT)
    {
        this->logger->log(ERROR, "Make request error (not client role)");
        throw RequestMakeErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (inf.manager_id != NONE)
    {
        this->logger->log(ERROR, "Make request error (manager exists)");
        throw RequestMakeErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    // check fullness of client account
    std::vector<Client> clients = this->clientRepository->getAllClients();
    int id = NONE;
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getUserID() == user_id)
            id = clients[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Make request error (client not found)");
        throw RequestMakeErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Product tmpProduct = this->productRepository->getProductByID(inf.product_id);
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Make request error (product not found)");
        throw ProductNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if ((tmpProduct.getMinSum() > inf.sum) || (tmpProduct.getMaxSum() < inf.sum) || (tmpProduct.getMinTime() > inf.duration) 
    || (tmpProduct.getMaxTime() < inf.duration))
    {
        this->logger->log(ERROR, "Make request error (incorrect sum or duration)");
        throw RequestMakeErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    id = RequestRules::addRequest(inf);
    this->logger->log(INFO, "Make request success");
    return id;
}

void RequestRules::rateProduct(int req_id, int user_id, int rating)
{
    Request tmpRequest = this->repository->getRequestByID(req_id);
    if (tmpRequest.getID() == NONE)
    {
        this->logger->log(ERROR, "Rate product error (request not found)");
        throw RequestNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Client> clients = this->clientRepository->getAllClients();
    int id = NONE;
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getUserID() == user_id)
            id = clients[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Rate product error (client not found)");
        throw ProductRateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpRequest.getClientID() != id)
    {
        this->logger->log(ERROR, "Rate product error (attempt to rate not own request)");
        throw ProductRateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if ((tmpRequest.getState() != CLOSED) && (tmpRequest.getState() != APPROVED))
    {
        this->logger->log(ERROR, "Rate product error (incorrect state of request)");
        throw ProductRateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Product tmpProduct = this->productRepository->getProductByID(tmpRequest.getProductID());
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Rate product error (product not found)");
        throw ProductRateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    tmpProduct.incSumRating(rating);
    tmpProduct.incCountRating();
    if (tmpRequest.getState() == APPROVED)
        tmpRequest.setState(APPROVED_SCORED);
    if (tmpRequest.getState() == CLOSED)
        tmpRequest.setState(CLOSED_SCORED);
    this->productRepository->updateEl(tmpProduct);
    this->repository->updateEl(tmpRequest);
    this->logger->log(INFO, "Rate product success");
}

void RequestRules::confirmRequest(int req_id, int manager_id)
{
    Request tmpRequest = this->repository->getRequestByID(req_id);
    if (tmpRequest.getID() == NONE)
    {
        this->logger->log(ERROR, "Confirm request error (request not found)");
        throw RequestNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Manager tmpManager = this->managerRepository->getManagerByID(manager_id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Confirm request error (manager not found)");
        throw RequestConfirmErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Product tmpProduct = this->productRepository->getProductByID(tmpRequest.getProductID());
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Confirm request error (product not found)");
        throw RequestConfirmErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpProduct.getBankID() != tmpManager.getBankID())
    {
        this->logger->log(ERROR, "Confirm request error (bank_id request != bank_id manager)");
        throw RequestConfirmErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpRequest.getState() != OPENED)
    {
        this->logger->log(ERROR, "Confirm request error (state of request is not OPENED)");
        throw RequestConfirmErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    tmpRequest.setManagerID(manager_id);
    tmpRequest.setState(APPROVED);
    this->repository->updateEl(tmpRequest);
    this->logger->log(INFO, "Confirm request success");
}

void RequestRules::rejectRequest(int req_id, int manager_id)
{
    Request tmpRequest = this->repository->getRequestByID(req_id);
    if (tmpRequest.getID() == NONE)
    {
        this->logger->log(ERROR, "Reject request error (request not found)");
        throw RequestNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Manager tmpManager = this->managerRepository->getManagerByID(manager_id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Reject request error (manager not found)");
        throw RequestRejectErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Product tmpProduct = this->productRepository->getProductByID(tmpRequest.getProductID());
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Reject request error (product not found)");
        throw RequestRejectErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpProduct.getBankID() != tmpManager.getBankID())
    {
        this->logger->log(ERROR, "Reject request error (bank_id request != bank_id manager)");
        throw RequestRejectErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpRequest.getState() != OPENED)
    {
        this->logger->log(ERROR, "Reject request error (state of request is not OPENED)");
        throw RequestRejectErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    tmpRequest.setManagerID(manager_id);
    tmpRequest.setState(REJECTED);
    this->repository->updateEl(tmpRequest);
    this->logger->log(INFO, "Reject request success");
}

void RequestRules::updateRequest(Request req_el)
{
    if ((req_el.getDuration() < MIN_TIME) || (req_el.getSum() < MIN_SUM) || (req_el.getState() < OPENED) ||
            (req_el.getState() > CLOSED))
    {
        this->logger->log(ERROR, "Update request error (incorrect params)");
        throw RequestUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Client> clients = this->clientRepository->getAllClients();
    int id = NONE;
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getID() == req_el.getClientID())
            id = clients[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Update request error (client not found)");
        throw RequestUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (req_el.getManagerID() != NONE)
    {
        id = NONE;
        std::vector<Manager> managers = this->managerRepository->getAllManagers();
        for (size_t i = 0; i < managers.size(); i++)
            if (managers[i].getID() == req_el.getManagerID())
                id = managers[i].getID();
        if (id == NONE)
        {
            this->logger->log(ERROR, "Update request error (manager not found)");
            throw RequestUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    this->repository->updateEl(req_el);
    this->logger->log(INFO, "Update request success");
}

void RequestRules::deleteRequest(int id)
{
    Request tmpRequest = this->repository->getRequestByID(id);
    if (tmpRequest.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            Request testRequest = this->repository->getRequestByID(id);
            if (testRequest.getID() != NONE)
            {
                this->logger->log(ERROR, "Delete request error (can not delete)");
                throw RequestDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
            }
            this->logger->log(INFO, "Delete request success");
        }
        catch (RequestNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "Delete request error (request not found)");
        throw RequestNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

int RequestRules::addRequest(RequestInfo inf)
{
    if ((inf.duration < MIN_TIME) || (inf.sum < MIN_SUM) || (inf.state != OPENED))
    {
        this->logger->log(ERROR, "Add request error (incorrect params)");
        throw RequestAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Client> clients = this->clientRepository->getAllClients();
    int id = NONE;
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getID() == inf.client_id)
            id = clients[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Add request error (client not found)");
        throw RequestAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    id = this->repository->addRequest(inf);
    Request tmpRequest = this->repository->getRequestByID(id);
    if (tmpRequest.getID() == NONE)
    {
        this->logger->log(ERROR, "Add request error (can not add)");
        throw RequestAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Add request success");
    return id;
}

std::vector<Request> RequestRules::getAllRequests()
{
    std::vector<Request> requests = this->repository->getAllRequests();
    this->logger->log(INFO, "Get all requests success");
    return requests;
}
