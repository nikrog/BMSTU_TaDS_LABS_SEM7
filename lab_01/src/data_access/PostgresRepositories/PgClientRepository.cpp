#include "PgClientRepository.h"

Client PgClientRepository::getClientByID(int id)
{
    Client resultClient;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetClientByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultClient = Client(id, result[0][9].as<int>(), result[0][1].as<std::string>(), result[0][2].as<std::string>(), 
                                  result[0][3].as<std::string>(), result[0][4].as<passport_t>(), result[0][5].as<date_t>(),
                                   result[0][6].as<std::string>(), result[0][7].as<std::string>(), result[0][8].as<std::string>());
            }
            else
                resultClient = Client();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultClient; 
}

std::vector<Client> PgClientRepository::getClientByFIO(FIO name)
{
    std::vector<Client> resultClients = std::vector<Client>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetClientByFIO().get_str(name);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Client currentClient = Client(result[i][0].as<int>(), result[i][9].as<int>(), result[i][1].as<std::string>(), result[i][2].as<std::string>(), 
                                  result[i][3].as<std::string>(), result[i][4].as<passport_t>(), result[i][5].as<date_t>(),
                                   result[i][6].as<std::string>(), result[i][7].as<std::string>(), result[i][8].as<std::string>());
                resultClients.push_back(currentClient);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultClients;
}

std::vector<Client> PgClientRepository::getAllClients()
{
    std::vector<Client> resultClients = std::vector<Client>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllClients().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Client currentClient = Client(result[i][0].as<int>(), result[i][9].as<int>(), result[i][1].as<std::string>(), result[i][2].as<std::string>(), 
                                  result[i][3].as<std::string>(), result[i][4].as<passport_t>(), result[i][5].as<date_t>(),
                                   result[i][6].as<std::string>(), result[i][7].as<std::string>(), result[i][8].as<std::string>());
                resultClients.push_back(currentClient);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultClients;
}

int PgClientRepository::addClient(ClientInfo inf)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddClient().get_str(inf);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() == 1)
            {
                res_id = result[0][0].as<int>();
            }
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return res_id;
}

void PgClientRepository::deleteEl(int id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteClient().get_str(id);
            pqxx::work curConnect(*this->connection);
            curConnect.exec(sql);
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
}

void PgClientRepository::updateEl(Client client_el)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateClient().get_str(client_el);
            pqxx::work curConnect(*this->connection);
            curConnect.exec(sql);
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
}
