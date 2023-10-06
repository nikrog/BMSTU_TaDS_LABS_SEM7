#ifndef PPO_MANAGERSMANAGER_H
#define PPO_MANAGERSMANAGER_H

#include "ManagerGetter.h"
#include "ManagerPrinter.h"
#include "../../business_logic/rules/ManagerRules.h"
#include "../../business_logic/rules/UserRules.h"

class ManagersManager {
private:
    ManagerGetter getter;
    ManagerPrinter printer;
    ManagerRules managerController;
    UserRules userController;
public:
    ManagersManager(ManagerRules &mController, UserRules &uController);
    ManagersManager();
    ~ManagersManager() = default;
    void addManager();
    void viewManager();
    void viewAllManagers();
    void changeManagerInfo();
    int getManagerByUserID(int user_id);
};


#endif //PPO_MANAGERSMANAGER_H
