#ifndef PPO_PGREQUESTREPOSITORY_H
#define PPO_PGREQUESTREPOSITORY_H

#include "../../business_logic/models/ModelRequest.h"
#include "../../business_logic/IRepositories/IRequestRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgRequestRepository : public IRequestRepository {
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgRequestRepository(ConnectionParams params): IRequestRepository() {
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
    ~PgRequestRepository() = default;

    Request getRequestByID(int id) override;
    std::vector<Request> getRequestByState(State_t state) override;
    std::vector<Request> getRequestByDate(timereq_t date) override;
    std::vector<Request> getRequestByClient(int client_id) override;
    std::vector<Request> getRequestByManager(int manager_id) override;
    std::vector<Request> getRequestBySum(float min_sum, float max_sum) override;
    std::vector<Request> getRequestByDuration(int min_time, int max_time) override;
    std::vector<Request> getAllRequests() override;
    void callRateProduct(int req_id, int score) override;
    void callMakeRequest(int cl_id, int prod_id, float sum, int dur) override;
    void callConfirmRequest(int req_id, int manager_id) override;
    void callRejectRequest(int req_id, int manager_id) override;

    int addRequest(RequestInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Request req_el) override;
};


#endif //PPO_PGREQUESTREPOSITORY_H
