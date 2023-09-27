#ifndef PPO_IMANAGERREPOSITORY_H
#define PPO_IMANAGERREPOSITORY_H

#include "../models/ModelManager.h"
#include "CRUDRepository.h"

class IManagerRepository : public CRUDRepository<Manager> {
public:
    virtual Manager getManagerByID(int id) = 0;
    virtual Manager getManagerByUID(int user_id) = 0;
    virtual std::vector<Manager> getManagerByBank(int bank_id) = 0;
    virtual std::vector<Manager> getAllManagers() = 0;
    virtual int addManager(int user_id, int bank_id) = 0;
};


#endif //PPO_IMANAGERREPOSITORY_H
