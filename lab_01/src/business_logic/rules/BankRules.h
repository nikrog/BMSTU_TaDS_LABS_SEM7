#ifndef PPO_BANKRULES_H
#define PPO_BANKRULES_H

#include "../models/ModelBank.h"
#include "../IRepositories/IBankRepository.h"
#include "../exceptions/exceptions.h"
#include "ILogger.h"

class BankRules {
private:
    IBankRepository *repository;
    ILogger *logger;
public:
    BankRules(IBankRepository &repository, ILogger &logger);
    BankRules();
    ~BankRules();

    Bank getBank(int id);
    Bank getBankByName(std::string name);
    void updateBank(Bank bank_el);
    void deleteBank(int id);
    int addBank(BankInfo inf);
    std::vector<Bank> getAllBanks();
};


#endif //PPO_BANKRULES_H
