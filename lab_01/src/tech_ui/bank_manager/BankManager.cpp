#include "BankManager.h"

BankManager::BankManager(BankRules &bController)
{
    this->bankController = bController;
    this->printer = BankPrinter();
}

BankManager::BankManager(){}

void BankManager::printAllBanks()
{
    std::vector<Bank> banks = this->bankController.getAllBanks();
    for (size_t i = 0; i < banks.size(); i++)
        this->printer.printBank(banks[i]);
}