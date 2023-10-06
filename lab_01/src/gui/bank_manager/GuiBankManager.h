#ifndef PPO_GUIBANKMANAGER_H
#define PPO_GUIBANKMANAGER_H

#include "../../business_logic/rules/BankRules.h"

class GUIBankManager {
private:
    BankRules bankController;
public:
    GUIBankManager(BankRules &bController);
    GUIBankManager();
    ~GUIBankManager() = default;
    std::vector<Bank> printAllBanks();
    Bank viewBank(int bank_id);
    std::string getBankNameByID(int id);
    int getBankIDByName(std::string name);
    void deleteBank(int bank_id);
    void updateBank(int bank_id, BankInfo inf);
    int addBank(BankInfo inf);
};


#endif //PPO_GUIBANKMANAGER_H
