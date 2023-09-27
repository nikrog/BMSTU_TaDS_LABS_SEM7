#ifndef PPO_AUTHMANAGER_H
#define PPO_AUTHMANAGER_H

#include "AuthGetter.h"
#include "AuthPrinter.h"
#include "../../business_logic/rules/UserRules.h"

class AuthManager {
private:
    AuthGetter getter;
    AuthPrinter printer;
    std::string login;
    std::string password;
    UserRules controller;
public:
    AuthManager(UserRules &controller);
    AuthManager();
    ~AuthManager() = default;
    bool isAuthorized(std::string login);
    Roles tryToAuthorize();
    int getUserID(std::string login);
    std::string getLogin();
};


#endif //PPO_AUTHMANAGER_H
