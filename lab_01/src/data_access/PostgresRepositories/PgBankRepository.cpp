#include "PgBankRepository.h"

Bank PgBankRepository::getBankByID(int id)
{
    Bank resultBank;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetBankByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultBank = Bank(id, result[0][1].as<std::string>(), result[0][2].as<int>(),
                                  result[0][3].as<std::string>(), result[0][4].as<std::string>(),
                                  result[0][5].as<std::string>(), result[0][6].as<std::string>());
            }
            else
                resultBank = Bank();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultBank;   
}

Bank PgBankRepository::getBankByName(std::string name)
{
    Bank resultBank;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetBankByName().get_str(name);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultBank = Bank(result[0][0].as<int>(), result[0][1].as<std::string>(), result[0][2].as<int>(),
                                  result[0][3].as<std::string>(), result[0][4].as<std::string>(),
                                  result[0][5].as<std::string>(), result[0][6].as<std::string>());
            }
            else
                resultBank = Bank();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultBank;  
}

std::vector<Bank> PgBankRepository::getAllBanks()
{
    std::vector<Bank> resultBanks = std::vector<Bank>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllBanks().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Bank currentBank = Bank(result[i][0].as<int>(), result[i][1].as<std::string>(), result[i][2].as<int>(),
                                  result[i][3].as<std::string>(), result[i][4].as<std::string>(),
                                  result[i][5].as<std::string>(), result[i][6].as<std::string>());
                resultBanks.push_back(currentBank);
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
    return resultBanks;
}

int PgBankRepository::addBank(BankInfo inf)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddBank().get_str(inf);
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

void PgBankRepository::deleteEl(int id) 
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteBank().get_str(id);
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

void PgBankRepository::updateEl(Bank bank_el) 
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateBank().get_str(bank_el);
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