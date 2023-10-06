#include "ManagerRules.h"

ManagerRules::ManagerRules(IManagerRepository &repository, IBankRepository &bankRepository,
                           IUserRepository &userRepository, IClientRepository &clientRepository, ILogger &logger) {
    this->repository = &repository;
    this->bankRepository = &bankRepository;
    this->userRepository = &userRepository;
    this->clientRepository = &clientRepository;
    this->logger = &logger;
}

ManagerRules::ManagerRules()
{}

ManagerRules::~ManagerRules()
{}

Manager ManagerRules::getManager(int id) {
    Manager tmpManager = this->repository->getManagerByID(id);

    User tmpUser = this->userRepository->getUserByID(id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager not found");
        throw ManagerNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get manager success");
        return tmpManager;
    }
}

std::vector<Manager> ManagerRules::getManagerByBank(int bank_id)
{
    std::vector<Manager> managers = this->repository->getManagerByBank(bank_id);
    this->logger->log(INFO, "Get manager by bank success");
    return managers;
}

int ManagerRules::addManager(int user_id, int bank_id) {
    if ((user_id <= NONE) || (bank_id <= NONE))
    {
        this->logger->log(ERROR, "Manager add error (incorrect user_id or bank_id)");
        throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    User tmpUser = this->userRepository->getUserByID(user_id);
    if (tmpUser.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager add error (user_id not found)");
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Bank tmpBank = this->bankRepository->getBankByID(bank_id);
    if (tmpBank.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager add error (bank_id not found)");
        throw BankNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Manager> managers = this->repository->getAllManagers();
    for (size_t i = 0; i < managers.size(); i++)
        if (managers[i].getUserID() == user_id)
        {
            this->logger->log(ERROR, "Manager add error (user_id is busy)");
            throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    std::vector<Client> clients = this->clientRepository->getAllClients();
    for (size_t i = 0; i < clients.size(); i++)
        if (clients[i].getUserID() == user_id)
        {
            this->logger->log(ERROR, "Manager add error (user_id is busy)");
            throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    int id = this->repository->addManager(user_id, bank_id);
    tmpUser = this->userRepository->getUserByID(user_id);
    tmpUser.setPermission(MANAGER);
    this->userRepository->updateEl(tmpUser);
    Manager tmpManager = this->repository->getManagerByID(id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager add error (can not add)");
        throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Manager add success");
    return id;
}

void ManagerRules::deleteManager(int id) {
    Manager tmpManager = this->repository->getManagerByID(id);
    if (tmpManager.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            Manager testManager = this->repository->getManagerByID(id);
            if (testManager.getID() != NONE)
            {
                this->logger->log(ERROR, "Manager delete error (can not delete)");
                throw ManagerDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
            }
        }
        catch (ManagerNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "Manager delete error (manager not found)");
        throw ManagerNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Manager delete success");
}

void ManagerRules::updateManagerBank(int id, int bank_id) {
    Manager tmpManager = this->repository->getManagerByID(id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager update error (manager not found)");
        throw ManagerNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    Bank tmpBank = this->bankRepository->getBankByID(bank_id);
    if (tmpBank.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager update error (bank not found)");
        throw BankNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    tmpManager.setBankID(bank_id);
    this->repository->updateEl(tmpManager);
    tmpManager = this->repository->getManagerByID(id);
    if (tmpManager.getID() == NONE)
    {
        this->logger->log(ERROR, "Manager update error (can not update)");
        throw ManagerNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (tmpManager.getBankID() != bank_id)
    {
        this->logger->log(ERROR, "Manager update error (can not update)");
        throw ManagerUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Manager update success");
}

std::vector<Manager> ManagerRules::getAllManagers() {
    std::vector<Manager> managers = this->repository->getAllManagers();
    this->logger->log(INFO, "Get all managers success");
    return managers;
}