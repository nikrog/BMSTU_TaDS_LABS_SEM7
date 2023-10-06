#ifndef PPO_BANKSTUB_H
#define PPO_BANKSTUB_H

#include "../../src/business_logic/models/ModelBank.h"
#include "../../src/business_logic/IRepositories/IBankRepository.h"

class BankStub : public IBankRepository{
private:
    std::vector<Bank> banks;
public:
    BankStub(): IBankRepository() {
        std::vector<Bank> b = {Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"),
        Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru")};
        this->banks = b;
    }
    ~BankStub();
    Bank getBankByID(int id) override;
    Bank getBankByName(std::string name) override;
    std::vector<Bank> getAllBanks() override;
    int addBank(BankInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Bank bank_el) override;
};


#endif //PPO_BANKSTUB_H