#include "AuthManager.h"

AuthManager::AuthManager(UserRules &controller)
{
    this->controller = UserRules(controller);
    this->getter = AuthGetter();
    this->printer = AuthPrinter();
    this->login = std::string();
    this->password = std::string();
}

AuthManager::AuthManager() {}

bool AuthManager::isAuthorized(std::string login)
{
    return this->controller.isUserExists(login);
}

Roles AuthManager::tryToAuthorize()
{
    Roles result = NON_AUTH;
    this->printer.print_login_entry();
    this->login = this->getter.getString();
    this->printer.print_password_entry();
    this->password = this->getter.getString();
    try
    {
        result = this->controller.authUser(login, password);
        if (result == NON_AUTH)
        { 
            throw IncorrectPasswordOrLoginException(__FILE__, typeid(*this).name(), __LINE__);
        }
        else
        {
            this->printer.print_success();
        }
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
    return result;
}

int AuthManager::getUserID(std::string login)
{
    int result = NONE;
    try
    {
        if (this->controller.isUserExists(login))
            result = this->controller.getUserID(login);
        else
            throw LoginNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
        this->printer.printException(e);
    }
    return result;
}

std::string AuthManager::getLogin()
{
    return this->login;
}