#ifndef PPO_MOCKMANAGERREPOSITORY_H
#define PPO_MOCKMANAGERREPOSITORY_H

#include "../../business_logic/models/ModelManager.h"
#include "../../business_logic/IRepositories/IManagerRepository.h"

class MockManagerRepository : public IManagerRepository{
private:
    std::vector<Manager> managers;
public:
    MockManagerRepository(std::vector<Manager> managers): IManagerRepository(), managers(managers) {

    }
    ~MockManagerRepository();
    Manager getManagerByID(int id) override;
    Manager getManagerByUID(int user_id) override;
    std::vector<Manager> getManagerByBank(int bank_id) override;
    std::vector<Manager> getAllManagers() override;
    void updateEl(Manager manager_el) override;
    void deleteEl(int id) override;
    int addManager(int user_id, int bank_id) override;
};


#endif //PPO_MOCKMANAGERREPOSITORY_H
