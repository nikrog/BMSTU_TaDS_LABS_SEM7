#include "MockBankRepository.h"

 MockBankRepository::~MockBankRepository()
 {}
 
Bank MockBankRepository::getBankByID(int id)
{
    for (Bank tmpBank : this->banks)
    {
        if (tmpBank.getID() == id)
            return tmpBank;
    }
    
    return Bank();
}
Bank MockBankRepository::getBankByName(std::string name)
{
    for (Bank tmpBank : this->banks)
    {
        if (tmpBank.getName() == name)
            return tmpBank;
    }
    
    return Bank();
}
std::vector<Bank> MockBankRepository::getAllBanks()
{
    return this->banks;
}
int MockBankRepository::addBank(BankInfo inf)
{
    int N = this->banks.size();
    Bank tmpBank = Bank(N + 1, inf.name, inf.license_num, inf.address, inf.email, inf.phone, inf.website);
    this->banks.push_back(tmpBank);
    return N + 1;
}
void MockBankRepository::deleteEl(int id)
{
    std::vector<Bank> new_banks;
    for (Bank tmpBank : this->banks)
    {
        if (tmpBank.getID() != id)
            new_banks.push_back(tmpBank);
    }
    this->banks = new_banks;
}
void MockBankRepository::updateEl(Bank bank_el)
{
    for (Bank tmpBank : this->banks)
    {
        if (tmpBank.getID() == bank_el.getID())
        {
            this->banks[tmpBank.getID() - 1].setName(bank_el.getName());
            this->banks[tmpBank.getID() - 1].setLicenseNum(bank_el.getLicenseNum());
            this->banks[tmpBank.getID() - 1].setAddress(bank_el.getAddress());
            this->banks[tmpBank.getID() - 1].setEmail(bank_el.getEmail());
            this->banks[tmpBank.getID() - 1].setPhone(bank_el.getPhone());
            this->banks[tmpBank.getID() - 1].setWebsite(bank_el.getWebsite());
        }
    }
    return;
}