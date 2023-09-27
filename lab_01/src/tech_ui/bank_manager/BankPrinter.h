#ifndef PPO_BANKPRINTER_H
#define PPO_BANKPRINTER_H

#include <iostream>
#include <string>
#include "../../business_logic/models/ModelBank.h"

class BankPrinter {
public:
    BankPrinter() = default;
    ~BankPrinter() = default;
    void printBank(Bank bank_el);
};


#endif //PPO_BANKPRINTER_H
