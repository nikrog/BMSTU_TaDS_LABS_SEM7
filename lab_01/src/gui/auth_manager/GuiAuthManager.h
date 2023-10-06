#ifndef PPO_GUIAUTHMANAGER_H
#define PPO_GUIAUTHMANAGER_H

#include "../../business_logic/rules/UserRules.h"

class GUIAuthManager {
private:
    std::string login;
    std::string password;
    UserRules controller;
public:
    GUIAuthManager(UserRules &controller);
    GUIAuthManager();
    ~GUIAuthManager() = default;
    bool isAuthorized(std::string login);
    Roles tryToAuthorize(std::string login, std::string password);
    int getUserID(std::string login);
    std::string getLogin();
    std::vector<User> viewAllUsers();
    void changePassword(int user_id, std::string new_password);
    void deleteUser(int user_id);
    User viewUser(int user_id);
    void setRole(Roles role);
};


#endif //PPO_GUIAUTHMANAGER_H
