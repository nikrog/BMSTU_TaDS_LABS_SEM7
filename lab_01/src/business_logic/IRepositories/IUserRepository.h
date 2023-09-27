#ifndef PPO_IUSERREPOSITORY_H
#define PPO_IUSERREPOSITORY_H

#include "../models/ModelUser.h"
#include "CRUDRepository.h"
#include <iostream>
#include <string>
#include <vector>


class IUserRepository: public CRUDRepository<User> {
public:
    virtual int getUserID(std::string login) = 0;
    virtual User getUserByID(int id) = 0;
    virtual User getUserByLogin(std::string login) = 0;
    virtual void setRole(Roles role) = 0;

    virtual int addUser(UserInfo inf) = 0;
    virtual std::vector<User> getAllUsers() = 0;
};


#endif //PPO_IUSERREPOSITORY_H
