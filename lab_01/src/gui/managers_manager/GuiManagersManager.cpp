#include "GuiManagersManager.h"

GUIManagersManager::GUIManagersManager(ManagerRules &mController, UserRules &uController)
{
    this->managerController = mController;
    this->userController = uController;
}

GUIManagersManager::GUIManagersManager() {}

void GUIManagersManager::addManager(int bank_id, std::string login, std::string password)
{

    int userID = this->userController.addUser({.login=login, .password = password, .permission = MANAGER});
    try
    {
        int m_id = this->managerController.addManager(userID, bank_id);
        Manager tmpManager = this->managerController.getManager(m_id);
        if (tmpManager.getID() == NONE)
        {
            throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
        this->userController.deleteUser(userID);
        throw ManagerAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

Manager GUIManagersManager::viewManager(int id)
{
    Manager tmpManager = this->managerController.getManager(id);
    return tmpManager;
}

std::vector<Manager> GUIManagersManager::viewAllManagers()
{
    std::vector<Manager> managers = this->managerController.getAllManagers();
    return managers;
}

void GUIManagersManager::changeManagerInfo(int id, int bank_id)
{   

    Manager tmpManager = this->managerController.getManager(id);
    if (tmpManager.getID() != NONE)
    {
        if (bank_id > 0)
        {
            this->managerController.updateManagerBank(tmpManager.getID(), bank_id);
        }
    }

}

int GUIManagersManager::getManagerByUserID(int user_id)
{
    int m_id = NONE;
    std::vector<Manager> managers = this->managerController.getAllManagers();
    for (size_t i = 0; i < managers.size(); i++)
    {
        if (managers[i].getUserID() == user_id)
        {
            m_id = managers[i].getID();
            break;
        }
    }
    return m_id;
}
