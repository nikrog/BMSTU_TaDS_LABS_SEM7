#include "GuiAuthManager.h"

GUIAuthManager::GUIAuthManager(UserRules &controller)
{
    this->controller = UserRules(controller);
    this->login = std::string();
    this->password = std::string();
}

GUIAuthManager::GUIAuthManager() {}

bool GUIAuthManager::isAuthorized(std::string login)
{
    return this->controller.isUserExists(login);
}

Roles GUIAuthManager::tryToAuthorize(std::string login, std::string password)
{
    Roles result = NON_AUTH;
    result = this->controller.authUser(login, password);
    if (result == NON_AUTH)
    { 
        throw IncorrectPasswordOrLoginException(__FILE__, typeid(*this).name(), __LINE__);
    }
    return result;
}

int GUIAuthManager::getUserID(std::string login)
{
    int result = NONE;
    if (this->controller.isUserExists(login))
        result = this->controller.getUserID(login);
    else
        throw LoginNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    return result;
}

std::string GUIAuthManager::getLogin()
{
    return this->login;
}

std::vector<User> GUIAuthManager::viewAllUsers()
{
    std::vector<User> users = this->controller.getAllUsers();
    return users;
}

void GUIAuthManager::changePassword(int user_id, std::string new_password)
{
    this->controller.updateUserPassword(user_id, new_password);
}

void GUIAuthManager::deleteUser(int user_id)
{
    this->controller.deleteUser(user_id);
}

User GUIAuthManager::viewUser(int user_id)
{
    User user = this->controller.getUser(user_id);
    return user;
}

void GUIAuthManager::setRole(Roles role)
{
    this->controller.setRole(role);
}
