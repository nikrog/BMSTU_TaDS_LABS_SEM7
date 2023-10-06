#include "ModelUser.h"

User::User(int id, std::string login, std::string password, Roles permission)
{
    this->id = id;
    this->login = login;
    this->password = password;
    this->permission = permission;
}

User::User()
{
    this->id = NONE;
    this->login = EMPTY;
    this->password = EMPTY;
    this->permission = NON_AUTH;
}

User::~User()
{}

int User::getID()
{
    return this->id;
}

std::string User::getLogin()
{
    return this->login;
}

std::string User::getPassword()
{
    return this->password;
}

Roles User::getUserRole()
{
    return this->permission;
}

void User::setLogin(std::string login)
{
    this->login = login;
}

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setPermission(Roles permission)
{
    this->permission = permission;
}

