#include "ClientRules.h"

ClientRules::ClientRules(IClientRepository &repository, IUserRepository &userRepository,
                         IManagerRepository &managerRepository, ILogger &logger)
{
    this->repository = &repository;
    this->userRepository = &userRepository;
    this->managerRepository = &managerRepository;
    this->logger = &logger;
}
ClientRules::ClientRules()
{}
ClientRules::~ClientRules()
{}

Client ClientRules::getClient(int id)
{
    Client tmpClient = this->repository->getClientByID(id);
    if (tmpClient.getID() == NONE)
    {
        this->logger->log(ERROR, "Client not found");
        throw ClientNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get client success");
        return tmpClient;
    }
}

std::vector<Client> ClientRules::getClientByFIO(FIO name)
{
    std::vector<Client> clients = this->repository->getClientByFIO(name);
    this->logger->log(INFO, "Get clients by FIO success");
    return clients;
}

void ClientRules::updateClient(Client client_el)
{
    if ((client_el.getName().length() < 1) || (client_el.getSurname().length() < 1) ||
    (client_el.getPatronymic().length() < 1) || (client_el.getPassportNum() < 1))
    {
        this->logger->log(ERROR, "Client update error (incorrect fio params length or passport_num)");
        throw ClientUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Manager> managers = this->managerRepository->getAllManagers();
    for (size_t i = 0; i < managers.size(); i++)
        if (managers[i].getUserID() == client_el.getUserID())
        {
            this->logger->log(ERROR, "Client update error (user_id is busy)");
            throw ClientUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    this->repository->updateEl(client_el);
    this->logger->log(INFO, "Client update success");
}

void ClientRules::deleteClient(int id)
{
    Client tmpClient = this->repository->getClientByID(id);
    if (tmpClient.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            Client testClient = this->repository->getClientByID(id);
            if (testClient.getID() != NONE)
            {
                this->logger->log(ERROR, "Delete client error (can not delete)");
                throw ClientDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
            }
        }
        catch (ClientNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "Delete client error (client not found)");
        throw ClientNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Delete client success");
}

int ClientRules::addClient(ClientInfo inf)
{
    if ((inf.name.length() < 1) || (inf.surname.length() < 1) ||
        (inf.patronymic.length() < 1) || (inf.passport_num < 1))
    {
        this->logger->log(ERROR, "Client add error (incorrect fio params length or passport_num)");
        throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    User tmpUser = this->userRepository->getUserByID(inf.user_id);
    if (tmpUser.getID() == NONE)
    {
        this->logger->log(ERROR, "Client add error (user not found)");
        throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Client> clients = this->repository->getAllClients();
    for (size_t i = 0; i < clients.size(); i++)
        if ((clients[i].getUserID() == inf.user_id) || (clients[i].getPassportNum() == inf.passport_num))
        {
            this->logger->log(ERROR, "Client add error (user_id or passport_num is busy)");
            throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    std::vector<Manager> managers = this->managerRepository->getAllManagers();
    for (size_t i = 0; i < managers.size(); i++)
        if (managers[i].getUserID() == inf.user_id)
        {
            this->logger->log(ERROR, "Client add error (user_id is busy)");
            throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    int id = this->repository->addClient(inf);
    Client tmpClient = this->repository->getClientByID(id);
    if (tmpClient.getID() == NONE)
    {
        this->logger->log(ERROR, "Client add error (can not add)");
        throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Client add success");
    return id;
}
std::vector<Client> ClientRules::getAllClients()
{
    std::vector<Client> clients = this->repository->getAllClients();
    this->logger->log(INFO, "Get all clients success");
    return clients;
}
