#include "UserOM.h"

UserOM::UserOM()
{}

UserOM::~UserOM()
{}

UserBuilder UserOM::guest(int id)
{
    UserBuilder obj = UserBuilder().withId(id).withLogin("guest").withPassword("guest").withRole(NON_AUTH);
    return obj;
}

UserBuilder UserOM::client(int id)
{
    char buf1[50], buf2[50];
    auto fmt1 = "user%d", fmt2 = "upassword%d";
    std::snprintf(buf1, 50, fmt1, id);
    std::snprintf(buf2, 50, fmt2, id);
    std::string login(buf1);
    std::string password(buf2);
    UserBuilder obj = UserBuilder().withId(id).withLogin(login).withPassword(password).withRole(CLIENT);
    return obj;
}

UserBuilder UserOM::manager(int id)
{
    char buf1[50], buf2[50];
    auto fmt1 = "manager%d", fmt2 = "mpassword%d";
    std::snprintf(buf1, 50, fmt1, id);
    std::snprintf(buf2, 50, fmt2, id);
    std::string login(buf1);
    std::string password(buf2);
    UserBuilder obj = UserBuilder().withId(id).withLogin(login).withPassword(password).withRole(MANAGER);
    return obj;
}

UserBuilder UserOM::admin(int id)
{
    char buf1[50], buf2[50];
    auto fmt1 = "admin%d", fmt2 = "apassword%d";
    std::snprintf(buf1, 50, fmt1, id);
    std::snprintf(buf2, 50, fmt2, id);
    std::string login(buf1);
    std::string password(buf2);
    UserBuilder obj = UserBuilder().withId(id).withLogin(login).withPassword(password).withRole(ADMIN);
    return obj;
}