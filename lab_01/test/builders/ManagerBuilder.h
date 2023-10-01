#ifndef PPO_MANAGERBUILDER_H
#define PPO_MANAGERBUILDER_H

#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/business_logic/rules/ManagerRules.h"

class ManagerBuilder {
    private:
        int id;
        int user_id;
        int bank_id;
    
    public:
        ManagerBuilder();
        ~ManagerBuilder();
        ManagerBuilder& withId(int id);
        ManagerBuilder& withUser(int user_id);
        ManagerBuilder& withBank(int bank_id);
        Manager build();
};

#endif //PPO_MANAGERBUILDER_H