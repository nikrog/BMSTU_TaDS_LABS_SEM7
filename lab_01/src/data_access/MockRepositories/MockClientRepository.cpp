#include "MockClientRepository.h"

MockClientRepository::~MockClientRepository()
{}

Client MockClientRepository::getClientByID(int id)
{
    for (Client tmpClient : this->clients)
    {
        if (tmpClient.getID() == id)
            return tmpClient;
    }
    
    return Client();
}
std::vector<Client> MockClientRepository::getClientByFIO(FIO name)
{
    std::vector<Client> res_clients;
    for (Client tmpClient : this->clients)
    {
        if ((tmpClient.getName() == name.name) && (tmpClient.getSurname() == name.surname) 
        && (tmpClient.getPatronymic() == name.patronymic))
            res_clients.push_back(tmpClient);
    }
    
    return res_clients;
}
std::vector<Client> MockClientRepository::getAllClients()
{
    return this->clients;
}
int MockClientRepository::addClient(ClientInfo inf)
{
    int N = this->clients.size();
    Client tmpClient = Client(N + 1, inf.user_id, inf.name, inf.surname, inf.patronymic, 
    inf.passport_num, inf.birth_date, inf.address, inf.email, inf.phone);
    this->clients.push_back(tmpClient);
    return N + 1;
}
void MockClientRepository::deleteEl(int id)
{
    std::vector<Client> new_clients;
    for (Client tmpClient : this->clients)
    {
        if (tmpClient.getID() != id)
            new_clients.push_back(tmpClient);
    }
    this->clients = new_clients;
}
void MockClientRepository::updateEl(Client client_el)
{
    for (Client tmpClient : this->clients)
    {
        if (tmpClient.getID() == client_el.getID())
        {
            this->clients[tmpClient.getID() - 1].setName(client_el.getName());
            this->clients[tmpClient.getID() - 1].setSurname(client_el.getSurname());
            this->clients[tmpClient.getID() - 1].setPatronymic(client_el.getPatronymic());
            this->clients[tmpClient.getID() - 1].setPassportNum(client_el.getPassportNum());
            this->clients[tmpClient.getID() - 1].setBirthDate(client_el.getBirthDate());
            this->clients[tmpClient.getID() - 1].setAddress(client_el.getAddress());
            this->clients[tmpClient.getID() - 1].setEmail(client_el.getEmail());
            this->clients[tmpClient.getID() - 1].setPhone(client_el.getPhone());
        }
    }
    return;
}