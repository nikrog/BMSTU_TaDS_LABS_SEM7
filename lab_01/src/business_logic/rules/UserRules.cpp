#include "UserRules.h"

UserRules::UserRules(IUserRepository &repository, ILogger &logger)
{
    this->repository = &repository;
    this->password_len = MIN_PASSWORD_LEN;
    this->login_len = MIN_LOGIN_LEN;
    this->logger = &logger;
}

UserRules::UserRules(IUserRepository &repository, ILogger &logger, int password_len, int login_len)
{
    this->repository = &repository;
    this->password_len = password_len;
    this->login_len = login_len;
    this->logger = &logger;
    //printf("%d", this->password_len);
}

UserRules::UserRules()
{}

UserRules::~UserRules()
{}

int UserRules::getUserID(std::string login)
{
    int id = this->repository->getUserID(login);
    if (id == NONE)
    {
        this->logger->log(ERROR, "User not found");
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get user id success");
        return id;
    }
}

User UserRules::getUser(int id)
{
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
    {
        this->logger->log(ERROR, "User not found");
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get user by id success");
        return tmpUser;
    }
}

int UserRules::addUser(UserInfo inf)
{
    printf("%d", this->password_len);
    if ((inf.permission > ADMIN) || (inf.permission < CLIENT))
        throw UserAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    if (inf.login.length() < this->login_len or inf.password.length() < this->password_len)
    {
        this->logger->log(ERROR, "User add error - incorrect length password or login");
        throw UserAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<User> users = this->repository->getAllUsers();
    for (size_t i = 0; i < users.size(); i++)
        if (users[i].getLogin() == inf.login)
        {
            this->logger->log(ERROR, "User add error - login is busy");
            throw UserAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
    int id = this->repository->addUser(inf);
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    return id;
}

void UserRules::deleteUser(int id) {
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            User testUser = this->repository->getUserByID(id);
            if (testUser.getID() != NONE)
                throw UserDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
        }
        catch (UserNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "User delete error - unexistent user");
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

void UserRules::updateUserLogin(int id, std::string new_login)
{
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if (new_login.length() < this->login_len)
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    std::vector<User> users = this->repository->getAllUsers();
    for (size_t i = 0; i < users.size(); i++)
        if (users[i].getLogin() == new_login)
            throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    tmpUser.setLogin(new_login);
    this->repository->updateEl(tmpUser);
    tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if (tmpUser.getLogin() != new_login)
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
}

void UserRules::updateUserPassword(int id, std::string new_password)
{
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if (new_password.length() < this->password_len)
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    tmpUser.setPassword(new_password);
    this->repository->updateEl(tmpUser);
    tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if (tmpUser.getPassword() != new_password)
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
}

void UserRules::updateUserPermission(int id, Roles new_permission) {
    User tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if ((new_permission > ADMIN) || (new_permission < CLIENT))
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    tmpUser.setPermission(new_permission);
    this->repository->updateEl(tmpUser);
    tmpUser = this->repository->getUserByID(id);
    if (tmpUser.getID() == NONE)
        throw UserNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    if (tmpUser.getUserRole() != new_permission)
        throw UserUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
}


bool UserRules::isUserExists(std::string login)
{
    return (this->repository->getUserID(login) > NONE);
}

std::vector<User> UserRules::getAllUsers()
{
    std::vector<User> users = this->repository->getAllUsers();
    return users;
}

Roles UserRules::authUser(std::string login, std::string password)
{
    Roles role = NON_AUTH;
    if (UserRules::isUserExists(login))
    {
        int tmpID = UserRules::getUserID(login);
        User tmpUser = UserRules::getUser(tmpID);
        if (tmpUser.getPassword() == password)
        {
            this->logger->log(INFO, "User authorization success");
            role = tmpUser.getUserRole();
        }
        else
            this->logger->log(ERROR, "User authorization failed");
    }
    else
        this->logger->log(ERROR, "User authorization failed");  
    return role;
}

int UserRules::getPasswLen()
{
    return this->password_len;
}

void UserRules::setRole(Roles role)
{
    this->repository->setRole(role);
    this->logger->log(INFO, "Set role succcess");
}
