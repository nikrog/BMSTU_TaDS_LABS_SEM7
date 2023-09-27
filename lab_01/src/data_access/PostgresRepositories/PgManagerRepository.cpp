#include "PgManagerRepository.h"

Manager PgManagerRepository::getManagerByID(int id)
{
    Manager resultManager;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetManagerByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultManager = Manager(id, result[0][1].as<int>(), result[0][2].as<int>());
            }
            else
                resultManager = Manager();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultManager;
}

Manager PgManagerRepository::getManagerByUID(int user_id)
{
    Manager resultManager;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetManagerByUID().get_str(user_id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultManager = Manager(result[0][0].as<int>(), result[0][1].as<int>(), result[0][2].as<int>());
            }
            else
                resultManager = Manager();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultManager;
}

std::vector<Manager> PgManagerRepository::getManagerByBank(int bank_id)
{
    std::vector<Manager> resultManagers = std::vector<Manager>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetManagerByBank().get_str(bank_id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Manager currentManager = Manager(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>());
                resultManagers.push_back(currentManager);
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
    return resultManagers;
}

std::vector<Manager> PgManagerRepository::getAllManagers()
{
    std::vector<Manager> resultManagers = std::vector<Manager>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllManagers().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Manager currentManager = Manager(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>());
                resultManagers.push_back(currentManager);
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
    return resultManagers;
}

void PgManagerRepository::updateEl(Manager manager_el)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateManager().get_str(manager_el);
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

void PgManagerRepository::deleteEl(int id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteManager().get_str(id);
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

int PgManagerRepository::addManager(int user_id, int bank_id)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddManager().get_str(user_id, bank_id);
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