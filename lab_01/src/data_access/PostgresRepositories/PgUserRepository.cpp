#include "PgUserRepository.h"

int PgUserRepository::getUserID(std::string login)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetUserID().get_str(login);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() == 1)
                res_id = result[0][0].as<int>();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return res_id;
}

User PgUserRepository::getUserByID(int id)
{
    User resultUser;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetUserByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultUser = User(id, result[0][1].as<std::string>(), result[0][2].as<std::string>(),
                                  Roles(result[0][3].as<int>()));
            }
            else
                resultUser = User();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultUser;     
}
User PgUserRepository::getUserByLogin(std::string login)
{
    User resultUser;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetUserByLogin().get_str(login);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultUser = User(result[0][0].as<int>(), result[0][1].as<std::string>(), result[0][2].as<std::string>(),
                                  Roles(result[0][3].as<int>()));
            }
            else
                resultUser = User();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultUser; 
}

int PgUserRepository::addUser(UserInfo inf)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddUser().get_str(inf);
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
void PgUserRepository::deleteEl(int id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteUser().get_str(id);
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
void PgUserRepository::updateEl(User user_el)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateUser().get_str(user_el);
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
std::vector<User> PgUserRepository::getAllUsers()
{

    std::vector<User> resultUsers = std::vector<User>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllUsers().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                User currentUser = User(result[i][0].as<int>(), result[i][1].as<std::string>(),
                                        result[i][2].as<std::string>(), Roles(result[i][3].as<int>()));
                resultUsers.push_back(currentUser);
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
    return resultUsers;
}

void PgUserRepository::setRole(Roles role)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLSetRole().get_str(role);
            pqxx::work curConnect(*this->connection);
            curConnect.exec(sql);
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
}
