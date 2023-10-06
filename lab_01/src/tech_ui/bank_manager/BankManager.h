#ifndef PPO_BANKMANAGER_H
#define PPO_BANKMANAGER_H

#include "BankPrinter.h"
#include "../../business_logic/rules/BankRules.h"

class BankManager {
private:
    BankRules bankController;
    BankPrinter printer;
public:
    BankManager(BankRules &bController);
    BankManager();
    ~BankManager() = default;
    void printAllBanks();
};


#endif //PPO_BANKMANAGER_H
