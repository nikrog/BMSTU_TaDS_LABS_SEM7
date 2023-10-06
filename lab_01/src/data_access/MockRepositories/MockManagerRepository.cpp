#include "MockManagerRepository.h"

MockManagerRepository::~MockManagerRepository()
{}

Manager MockManagerRepository::getManagerByID(int id)
{
    for (Manager tmpMan : this->managers)
    {
        if (tmpMan.getID() == id)
            return tmpMan;
    }
    
    return Manager();
}
Manager MockManagerRepository::getManagerByUID(int user_id)
{
    for (Manager tmpMan : this->managers)
    {
        if (tmpMan.getUserID() == user_id)
            return tmpMan;
    }

    return Manager();
}
std::vector<Manager> MockManagerRepository::getManagerByBank(int bank_id)
{
    std::vector<Manager> res_managers;
    for (Manager tmpMan : this->managers)
    {
        if (tmpMan.getBankID() == bank_id)
            res_managers.push_back(tmpMan);
    }
    return res_managers;
}
std::vector<Manager> MockManagerRepository::getAllManagers()
{
    return this->managers;
}
void MockManagerRepository::updateEl(Manager manager_el)
{
    for (Manager tmpMan : this->managers)
    {
        if (tmpMan.getID() == manager_el.getID())
        {
            this->managers[tmpMan.getID() - 1].setBankID(manager_el.getBankID());
        }
    }
    return;
}
void MockManagerRepository::deleteEl(int id)
{
    std::vector<Manager> new_managers;
    for (Manager tmpMan : this->managers)
    {
        if (tmpMan.getID() != id)
            new_managers.push_back(tmpMan);
    }
    this->managers = new_managers;
}
int MockManagerRepository::addManager(int user_id, int bank_id)
{
    int N = this->managers.size();
    Manager tmpMan = Manager(N + 1, user_id, bank_id);
    this->managers.push_back(tmpMan);
    return N + 1;
}