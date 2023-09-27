#ifndef PPO_MOCKUSERREPOSITORY_H
#define PPO_MOCKUSERREPOSITORY_H


#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/IRepositories/IUserRepository.h"

class MockUserRepository : public IUserRepository{
private:
    std::vector<User> users;
public:
    MockUserRepository(std::vector<User> users): IUserRepository(), users(users) {

    }
    ~MockUserRepository();
    int getUserID(std::string login) override;
    User getUserByID(int id) override;
    User getUserByLogin(std::string login) override;

    int addUser(UserInfo inf) override;
    void deleteEl(int id) override;
    void updateEl(User user_el) override;
    std::vector<User> getAllUsers() override;
};


#endif //PPO_MOCKUSERREPOSITORY_H
