#ifndef PPO_MODELUSER_H
#define PPO_MODELUSER_H

#include "constants.h"
#include <iostream>
#include <string>

enum Roles {
    NON_AUTH = 0,
    CLIENT = 1,
    MANAGER = 2,
    ADMIN = 3
};

class User {
private:
    int id;
    std::string login;
    std::string password;
    Roles permission;
public:
    User(int id, std::string login, std::string password, Roles permission);
    User();
    ~User();
    int getID();
    std::string getLogin();
    std::string getPassword();
    Roles getUserRole();

    void setLogin(std::string login);
    void setPassword(std::string password);
    void setPermission(Roles permission);
};

struct UserInfo {
    std::string login;
    std::string password;
    Roles permission;
};
#endif //PPO_MODELUSER_H
