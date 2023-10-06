#ifndef PPO_ICLIENTREPOSITORY_H
#define PPO_ICLIENTREPOSITORY_H

#include "../models/ModelClient.h"
#include "CRUDRepository.h"

class IClientRepository : public CRUDRepository<Client> {
public:
    virtual Client getClientByID(int id) = 0;
    virtual std::vector<Client> getClientByFIO(FIO name) = 0;
    virtual std::vector<Client> getAllClients() = 0;
    virtual int addClient(ClientInfo inf) = 0;
};


#endif //PPO_ICLIENTREPOSITORY_H
