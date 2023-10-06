#include "ManagersManager.h"

ManagersManager::ManagersManager(ManagerRules &mController, UserRules &uController)
{
    this->getter = ManagerGetter();
    this->printer = ManagerPrinter();
    this->managerController = mController;
    this->userController = uController;
}

ManagersManager::ManagersManager() {}

void ManagersManager::addManager()
{
    this->printer.printInputBankID();
    int bank_id = this->getter.getInt();

    this->printer.printInputLogin();
    std::string login = this->getter.getString();

    this->printer.printInputPassword();
    std::string password = this->getter.getString();

    try
    {
        this->userController.addUser({.login=login, .password = password, .permission = MANAGER});
        int userID = this->userController.getUserID(login);
        this->managerController.addManager(userID, bank_id);
        this->printer.printAddSuccess();
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

void ManagersManager::viewManager()
{
    this->printer.printInputID();
    int tmpID = this->getter.getInt();

    try
    {
        if (tmpID != NONE)
        {
            Manager tmpManager = this->managerController.getManager(tmpID);
            this->printer.printManager(tmpManager);
        }
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

void ManagersManager::viewAllManagers()
{
    std::vector<Manager> managers = this->managerController.getAllManagers();
    for (size_t i = 0; i < managers.size(); i++)
        this->printer.printManager(managers[i]);
}

void ManagersManager::changeManagerInfo()
{   
    this->printer.printInputID();
    int tmpID = this->getter.getInt();

    try
    {
        Manager tmpManager = this->managerController.getManager(tmpID);
        if (tmpManager.getID() != NONE)
        {
            this->printer.printInputBankID();
            int bank_id = this->getter.getInt();

            if (bank_id > 0)
            {
                this->managerController.updateManagerBank(tmpManager.getID(), bank_id);
                this->printer.printChangeInfoSuccess();
            }
        }
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

int ManagersManager::getManagerByUserID(int user_id)
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