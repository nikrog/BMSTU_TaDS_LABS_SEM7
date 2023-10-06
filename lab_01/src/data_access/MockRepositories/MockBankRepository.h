#ifndef PPO_MOCKBANKREPOSITORY_H
#define PPO_MOCKBANKREPOSITORY_H

#include "../../business_logic/models/ModelBank.h"
#include "../../business_logic/IRepositories/IBankRepository.h"

class MockBankRepository : public IBankRepository{
private:
    std::vector<Bank> banks;
public:
    MockBankRepository(std::vector<Bank> banks): IBankRepository(), banks(banks) {

    }
    ~MockBankRepository();
    Bank getBankByID(int id) override;
    Bank getBankByName(std::string name) override;
    std::vector<Bank> getAllBanks() override;
    int addBank(BankInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Bank bank_el) override;

};


#endif //PPO_MOCKBANKREPOSITORY_H
