#ifndef PPO_IBANKREPOSITORY_H
#define PPO_IBANKREPOSITORY_H

#include "../models/ModelBank.h"
#include "CRUDRepository.h"

class IBankRepository : public CRUDRepository<Bank> {
public:
    virtual Bank getBankByID(int id) = 0;
    virtual Bank getBankByName(std::string name) = 0;
    virtual std::vector<Bank> getAllBanks() = 0;
    virtual int addBank(BankInfo inf) = 0;
};


#endif //PPO_IBANKREPOSITORY_H
