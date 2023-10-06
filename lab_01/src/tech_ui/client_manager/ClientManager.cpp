#include "ClientManager.h"

ClientManager::ClientManager(ClientRules &cController, UserRules &uController)
{
    this->getter = ClientGetter();
    this->printer = ClientPrinter();
    this->clientController = cController;
    this->userController = uController;
}

ClientManager::ClientManager() {}

void ClientManager::addClient()
{
    this->printer.printInputName();
    std::string name = this->getter.getString();

    this->printer.printInputSurname();
    std::string surname = this->getter.getString();

    this->printer.printInputPatronymic();
    std::string patronymic = this->getter.getString();

    this->printer.printInputPassportNum();
    int passport_num = this->getter.getInt();

    this->printer.printInputAddress();
    std::string address = this->getter.getString();

    this->printer.printInputEmail();
    std::string email = this->getter.getString();

    this->printer.printInputPhone();
    std::string phone = this->getter.getString();

    this->printer.printInputBirthDate();
    date_t birth_date = this->getter.getInt();

    this->printer.printInputLogin();
    std::string login = this->getter.getString();

    this->printer.printInputPassword();
    std::string password = this->getter.getString();

    try
    {
        this->userController.addUser({.login=login, .password = password, .permission = CLIENT});
        int userID = this->userController.getUserID(login);
        this->clientController.addClient({.user_id=userID, .name=name, .surname=surname, .patronymic=patronymic,
        .passport_num=passport_num, .birth_date=birth_date, .address=address, .email=email, .phone=phone});
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

void ClientManager::viewClient()
{
    this->printer.printInputID();
    int tmpID = this->getter.getInt();

    try
    {
        if (tmpID != NONE)
        {
            Client tmpClient = this->clientController.getClient(tmpID);
            this->printer.printClient(tmpClient);
        }
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

void ClientManager::viewAllClients()
{
    std::vector<Client> clients = this->clientController.getAllClients();
    this->printer.printAllClients(clients);
}

void ClientManager::changeClientInfo()
{   
    this->printer.printInputID();
    int tmpID = this->getter.getInt();

    try
    {
        Client tmpClient = this->clientController.getClient(tmpID);
        if (tmpClient.getID() != NONE)
        {
            this->printer.printInputName();
            std::string name = this->getter.getString();

            if (!name.empty())
            {
                tmpClient.setName(name);
            }

            this->printer.printInputSurname();
            std::string surname = this->getter.getString();

            if (!surname.empty())
            {
                tmpClient.setSurname(surname);
            }

            this->printer.printInputPatronymic();
            std::string patronymic = this->getter.getString();

            if (!patronymic.empty())
            {
                tmpClient.setPatronymic(patronymic);
            }

            this->printer.printInputPassportNum();
            int passport_num = this->getter.getInt();

            if (passport_num > 0)
            {
                tmpClient.setPassportNum(passport_num);
            }

            this->printer.printInputAddress();
            std::string address = this->getter.getString();

            if (!address.empty())
            {
                tmpClient.setAddress(address);
            }

            this->printer.printInputEmail();
            std::string email = this->getter.getString();

            if (!email.empty())
            {
                tmpClient.setEmail(email);
            }

            this->printer.printInputPhone();
            std::string phone = this->getter.getString();

            if (!phone.empty())
            {
                tmpClient.setPhone(phone);
            }

            this->printer.printInputBirthDate();
            date_t birth_date = this->getter.getInt();

            if (birth_date > 19200101)
            {
                tmpClient.setBirthDate(birth_date);
            }

            this->clientController.updateClient(tmpClient);
        }
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
}

int ClientManager::getClientByUserID(int user_id)
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