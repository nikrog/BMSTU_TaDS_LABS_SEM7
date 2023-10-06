#ifndef PPO_PGUSERREPOSITORY_H
#define PPO_PGUSERREPOSITORY_H

#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/IRepositories/IUserRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgUserRepository : public IUserRepository{
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgUserRepository(ConnectionParams params): IUserRepository() {
        this->connect_str = params.getString();
        try
        {
            this->connection = std::make_shared<pqxx::connection>(
                              this->connect_str.c_str());
            if (!this->connection->is_open())
            {
                throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }
    }
    ~PgUserRepository() = default;
    int getUserID(std::string login) override;
    User getUserByID(int id) override;
    User getUserByLogin(std::string login) override;
    void setRole(Roles role) override;

    int addUser(UserInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(User user_el) override;
    std::vector<User> getAllUsers() override;
};


#endif //PPO_PGUSERREPOSITORY_H
