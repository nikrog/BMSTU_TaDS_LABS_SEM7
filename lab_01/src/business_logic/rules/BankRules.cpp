#include "BankRules.h"

BankRules::BankRules(IBankRepository &repository, ILogger &logger)
{
    this->repository = &repository;
    this->logger = &logger;
}
BankRules::BankRules()
{}
BankRules::~BankRules()
{}

Bank BankRules::getBank(int id)
{
    Bank tmpBank = this->repository->getBankByID(id);
    if (tmpBank.getID() == NONE)
    {
        this->logger->log(ERROR, "Bank not found");
        throw BankNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get bank success");
        return tmpBank;
    }
}

Bank BankRules::getBankByName(std::string name)
{
    Bank tmpBank = this->repository->getBankByName(name);
    if (tmpBank.getID() == NONE)
    {
        this->logger->log(ERROR, "Bank not found");
        throw BankNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get bank by name success");
        return tmpBank;
    }
}

void BankRules::updateBank(Bank bank_el)
{
    if ((bank_el.getName().length() < 1) || (bank_el.getLicenseNum() < 1))
    {
        this->logger->log(ERROR, "Bank update error (incorrect name length or license_num)");
        throw BankUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Bank update success");
    this->repository->updateEl(bank_el);
}

void BankRules::deleteBank(int id)
{
    Bank tmpBank = this->repository->getBankByID(id);
    if (tmpBank.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            Bank testBank = this->repository->getBankByID(id);
            if (testBank.getID() != NONE)
            {
                this->logger->log(ERROR, "Bank delete error (can not delete)");
                throw BankDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
            }
            this->logger->log(INFO, "Delete bank success");
        }
        catch (BankNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "Bank delete error (can not delete)");
        throw BankNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

int BankRules::addBank(BankInfo inf)
{
    if ((inf.name.length() < 1) || (inf.license_num < 1))
    {
        this->logger->log(ERROR, "Bank add error (incorrect name length or license_num)");
        throw BankAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    int id = this->repository->addBank(inf);
    Bank tmpBank = this->repository->getBankByID(id);
    if (tmpBank.getID() == NONE)
    {
        this->logger->log(ERROR, "Bank add error (can not add)");
        throw BankAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Add bank success");
    return id;
}

std::vector<Bank> BankRules::getAllBanks()
{
    this->logger->log(INFO, "Get all banks success");
    std::vector<Bank> banks = this->repository->getAllBanks();
    return banks;
}
