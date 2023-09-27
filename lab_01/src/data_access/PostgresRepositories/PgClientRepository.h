#ifndef PPO_PGCLIENTREPOSITORY_H
#define PPO_PGCLIENTREPOSITORY_H

#include "../../business_logic/models/ModelClient.h"
#include "../../business_logic/IRepositories/IClientRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgClientRepository : public IClientRepository {
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgClientRepository(ConnectionParams params): IClientRepository() {
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
    ~PgClientRepository() = default;

    Client getClientByID(int id) override;
    std::vector<Client> getClientByFIO(FIO name) override;
    std::vector<Client> getAllClients() override;
    int addClient(ClientInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Client client_el) override;
};


#endif //PPO_PGCLIENTREPOSITORY_H
