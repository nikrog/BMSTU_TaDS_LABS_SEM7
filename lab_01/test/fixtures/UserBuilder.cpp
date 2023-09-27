#include "UserBuilder.h"

UserBuilder::UserBuilder()
{
    this->id = NONE;
    this->login = EMPTY;
    this->password = EMPTY;
    this->permission = NON_AUTH;
}

UserBuilder::~UserBuilder()
{}

UserBuilder& UserBuilder::withId(int id)
{
    this->id = id;
    return *this;
}

UserBuilder& UserBuilder::withLogin(std::string login)
{
    this->login = login;
    return *this;
}

UserBuilder& UserBuilder::withPassword(std::string password)
{
    this->password = password;
    return *this;
}

UserBuilder& UserBuilder::withRole(Roles permission)
{
    this->permission = permission;
    return *this;
}

User UserBuilder::build()
{
    User user = User(this->id, this->login, this->password, this->permission);
    return user;
}