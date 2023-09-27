#include "GuiClientManager.h"

GUIClientManager::GUIClientManager(ClientRules &cController, UserRules &uController)
{
    this->clientController = cController;
    this->userController = uController;
}

GUIClientManager::GUIClientManager() {}

void GUIClientManager::addClient(ClientInfo inf, std::string login, std::string password)
{

    int userID = this->userController.addUser({.login=login, .password = password, .permission = CLIENT});
    User tmpUser = this->userController.getUser(userID);
    if (tmpUser.getID() == NONE)
    {
        throw UserAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    inf.user_id = userID;
    int id = this->clientController.addClient(inf);
    Client cl = this->clientController.getClient(id);
    if (cl.getID() == NONE)
    {
        throw ClientAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

Client GUIClientManager::viewClient(int id)
{
    Client tmpClient = this->clientController.getClient(id);
    return tmpClient;
}

std::vector<Client> GUIClientManager::viewAllClients()
{
    std::vector<Client> clients = this->clientController.getAllClients();
    return clients;
}

void GUIClientManager::changeClientInfo(int id, ClientInfo inf)
{
    Client tmpClient = this->clientController.getClient(id);
    if (tmpClient.getID() != NONE)
    {

        if (!inf.name.empty())
        {
            tmpClient.setName(inf.name);
        }

        if (!inf.surname.empty())
        {
            tmpClient.setSurname(inf.surname);
        }

        if (!inf.patronymic.empty())
        {
            tmpClient.setPatronymic(inf.patronymic);
        };

        if (inf.passport_num > 0)
        {
            tmpClient.setPassportNum(inf.passport_num);
        }

        if (!inf.address.empty())
        {
            tmpClient.setAddress(inf.address);
        }

        if (!inf.email.empty())
        {
            tmpClient.setEmail(inf.email);
        }

        if (!inf.phone.empty())
        {
            tmpClient.setPhone(inf.phone);
        }

        if (inf.birth_date > 0)
        {
            tmpClient.setBirthDate(inf.birth_date);
        }

        this->clientController.updateClient(tmpClient);
    }
}

int GUIClientManager::getClientByUserID(int user_id)
{
    int cl_id = NONE;
    std::vector<Client> clients = this->clientController.getAllClients();
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].getUserID() == user_id)
        {
            cl_id = clients[i].getID();
            break;
        }
    }
    return cl_id;
}

int GUIClientManager::fromDateToINT(std::string year, std::string month, std::string day)
{
    int y, m, d, i_date;
    y = std::stoi(year);
    m = std::stoi(month);
    d = std::stoi(day);
    i_date = y * 10000 + m * 100 + d;
    return i_date;
}

std::string GUIClientManager::fromINTtoDate(int i_date)
{
    int y, m, d;
    std::string s_date, s_m, s_d;
    y = i_date / 10000;
    m = i_date / 100 % 10;
    d = i_date % 100;
    if (m / 10 == 0)
    {
        s_m = "0" + std::to_string(m);
    }
    else
    {
        s_m = std::to_string(m);
    }
    if (d / 10 == 0)
    {
        s_d = "0" + std::to_string(d);
    }
    else
    {
        s_d = std::to_string(d);
    }
    s_date = s_d + "." + s_m + "." + std::to_string(y);
    return s_date;
}
