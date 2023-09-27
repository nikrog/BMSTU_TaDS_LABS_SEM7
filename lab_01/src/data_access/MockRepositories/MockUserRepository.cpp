#include "MockUserRepository.h"

MockUserRepository::~MockUserRepository()
{}

int MockUserRepository::getUserID(std::string login)
{
    for (User tmpUser : this->users)
    {
        if (tmpUser.getLogin() == login)
            return tmpUser.getID();
    }

    return NONE;
}

User MockUserRepository::getUserByID(int id)
{
    for (User tmpUser : this->users)
    {
        if (tmpUser.getID() == id)
            return tmpUser;
    }
    return User();
}

User MockUserRepository::getUserByLogin(std::string login)
{
    for (User tmpUser : this->users)
    {
        if (tmpUser.getLogin() == login)
            return tmpUser;
    }
    return User();
}

int MockUserRepository::addUser(UserInfo inf)
{
    int N = this->users.size();
    User tmpUser = User(N + 1, inf.login, inf.password, inf.permission);
    this->users.push_back(tmpUser);
    return N + 1;
}
void MockUserRepository::deleteEl(int id)
{
    std::vector<User> new_users;
    for (User tmpUser : this->users)
    {
        if (tmpUser.getID() != id)
            new_users.push_back(tmpUser);
    }
    this->users = new_users;
}
void MockUserRepository::updateEl(User user_el)
{
    for (User tmpUser : this->users)
    {
        if (tmpUser.getID() == user_el.getID())
        {
            this->users[tmpUser.getID() - 1].setLogin(user_el.getLogin());
            this->users[tmpUser.getID() - 1].setPassword(user_el.getPassword());
            this->users[tmpUser.getID() - 1].setPermission(user_el.getUserRole());
        }
    }
   
    return;
}
std::vector<User> MockUserRepository::getAllUsers()
{
    return this->users;
}