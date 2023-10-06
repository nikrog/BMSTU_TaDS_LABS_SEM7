#include "GuiBankManager.h"

GUIBankManager::GUIBankManager(BankRules &bController)
{
    this->bankController = bController;
}

GUIBankManager::GUIBankManager(){}

std::vector<Bank> GUIBankManager::printAllBanks()
{
    std::vector<Bank> banks = this->bankController.getAllBanks();
    return banks;
}

Bank GUIBankManager::viewBank(int id)
{
    Bank b = this->bankController.getBank(id);
    return b;
}

std::string GUIBankManager::getBankNameByID(int id)
{
    Bank bank = this->bankController.getBank(id);
    return bank.getName();
}

int GUIBankManager::getBankIDByName(std::string name)
{
    int id;
    try
    {
        Bank bank = this->bankController.getBankByName(name);
        id = bank.getID();
    }
    catch (const std::exception &e)
    {
        id = NONE;
    }
    return id;
}

void GUIBankManager::deleteBank(int bank_id)
{
    this->bankController.deleteBank(bank_id);
}

int GUIBankManager::addBank(BankInfo inf)
{
    int id = this->bankController.addBank(inf);
    return id;
}

void GUIBankManager::updateBank(int bank_id, BankInfo inf)
{
    Bank tmpBank = this->bankController.getBank(bank_id);
    if (tmpBank.getID() != NONE)
    {
        if (!inf.name.empty())
        {
            tmpBank.setName(inf.name);
        }

        if (!inf.website.empty())
        {
            tmpBank.setWebsite(inf.website);
        }

        if (inf.license_num > 0)
        {
            tmpBank.setLicenseNum(inf.license_num);
        }

        if (!inf.address.empty())
        {
            tmpBank.setAddress(inf.address);
        }

        if (!inf.email.empty())
        {
            tmpBank.setEmail(inf.email);
        }

        if (!inf.phone.empty())
        {
            tmpBank.setPhone(inf.phone);
        };

        this->bankController.updateBank(tmpBank);
    }
}
