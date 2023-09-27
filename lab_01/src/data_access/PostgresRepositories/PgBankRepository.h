#ifndef PPO_PGBANKREPOSITORY_H
#define PPO_PGBANKREPOSITORY_H

#include "../../business_logic/models/ModelBank.h"
#include "../../business_logic/IRepositories/IBankRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgBankRepository : public IBankRepository{
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgBankRepository(ConnectionParams params): IBankRepository() {
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
    ~PgBankRepository() = default;

    Bank getBankByID(int id) override;
    Bank getBankByName(std::string name) override;
    std::vector<Bank> getAllBanks() override;
    int addBank(BankInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Bank bank_el) override;
};


#endif //PPO_PGBANKREPOSITORY_H
