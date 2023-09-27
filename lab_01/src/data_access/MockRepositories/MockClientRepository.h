#ifndef PPO_MOCKCLIENTREPOSITORY_H
#define PPO_MOCKCLIENTREPOSITORY_H

#include "../../business_logic/models/ModelClient.h"
#include "../../business_logic/IRepositories/IClientRepository.h"

class MockClientRepository : public IClientRepository{
private:
    std::vector<Client> clients;
public:
    MockClientRepository(std::vector<Client> clients): IClientRepository(), clients(clients) {

    }
    ~MockClientRepository();
    Client getClientByID(int id) override;
    std::vector<Client> getClientByFIO(FIO name) override;
    std::vector<Client> getAllClients() override;
    int addClient(ClientInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(Client client_el) override;
};


#endif //PPO_MOCKCLIENTREPOSITORY_H
