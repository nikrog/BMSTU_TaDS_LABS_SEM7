#ifndef PPO_PGMANAGERREPOSITORY_H
#define PPO_PGMANAGERREPOSITORY_H

#include "../../business_logic/models/ModelManager.h"
#include "../../business_logic/IRepositories/IManagerRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgManagerRepository : public IManagerRepository{
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgManagerRepository(ConnectionParams params): IManagerRepository() {
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
    ~PgManagerRepository() = default;
    
    Manager getManagerByID(int id) override;
    Manager getManagerByUID(int user_id) override;
    std::vector<Manager> getManagerByBank(int bank_id) override;
    std::vector<Manager> getAllManagers() override;
    void updateEl(Manager manager_el) override;
    void deleteEl(int id) override;
    int addManager(int user_id, int bank_id) override;
};


#endif //PPO_PGMANAGERREPOSITORY_H
