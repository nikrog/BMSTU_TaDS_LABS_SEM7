#ifndef PPO_MODELMANAGER_H
#define PPO_MODELMANAGER_H

#include "constants.h"
#include <iostream>
#include <string>

class Manager {
private:
    int id;
    int user_id;
    int bank_id;
public:
    Manager(int id, int user_id, int bank_id);
    Manager();
    ~Manager();

    int getID();
    int getUserID();
    int getBankID();

    void setBankID(int bank_id);
};

#endif //PPO_MODELMANAGER_H
