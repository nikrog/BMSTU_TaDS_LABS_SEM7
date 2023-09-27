#ifndef PPO_MOCKREQUESTREPOSITORY_H
#define PPO_MOCKREQUESTREPOSITORY_H

#include "../../business_logic/models/ModelRequest.h"
#include "../../business_logic/IRepositories/IRequestRepository.h"

class MockRequestRepository : public IRequestRepository{
private:
    std::vector<Request> requests;
public:
    MockRequestRepository(std::vector<Request> requests): IRequestRepository(), requests(requests) {

    }
    ~MockRequestRepository();
    Request getRequestByID(int id) override;
    std::vector<Request> getRequestByState(State_t state) override;
    std::vector<Request> getRequestByDate(date_t date) override;
    std::vector<Request> getRequestByClient(int client_id) override;
    std::vector<Request> getRequestByManager(int manager_id) override;
    std::vector<Request> getRequestBySum(float min_sum, float max_sum) override;
    std::vector<Request> getRequestByDuration(int min_time, int max_time) override;
    std::vector<Request> getAllRequests() override;
    int addRequest(RequestInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Request req_el) override;
};


#endif //PPO_MOCKREQUESTREPOSITORY_H
