#ifndef PPO_GUIMANAGERSMANAGER_H
#define PPO_GUIMANAGERSMANAGER_H

#include "../../business_logic/rules/ManagerRules.h"
#include "../../business_logic/rules/UserRules.h"

class GUIManagersManager {
private:
    ManagerRules managerController;
    UserRules userController;
public:
    GUIManagersManager(ManagerRules &mController, UserRules &uController);
    GUIManagersManager();
    ~GUIManagersManager() = default;
    void addManager(int bank_id, std::string login, std::string password);
    Manager viewManager(int id);
    std::vector<Manager> viewAllManagers();
    void changeManagerInfo(int id, int bank_id);
    int getManagerByUserID(int user_id);
};


#endif //PPO_GUIMANAGERSMANAGER_H
