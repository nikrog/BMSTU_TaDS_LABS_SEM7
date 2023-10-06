#ifndef PPO_BANKOM_H
#define PPO_BANKOM_H

#include "BankBuilder.h"

class BankOM {
    public:
        BankOM();
        ~BankOM();
        BankBuilder filledBank(int id);
};

#endif //PPO_BANKOM_H