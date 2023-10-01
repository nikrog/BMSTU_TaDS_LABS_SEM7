#ifndef PPO_USERBUILDER_H
#define PPO_USERBUILDER_H

#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/rules/UserRules.h"

class UserBuilder {
    private:
        int id;
        std::string login;
        std::string password;
        Roles permission;
    
    public:
        //UserBuilder(int id, std::string login, std::string password, Roles permission);
        UserBuilder();
        ~UserBuilder();
        UserBuilder& withId(int id);
        UserBuilder& withLogin(std::string login);
        UserBuilder& withPassword(std::string password);
        UserBuilder& withRole(Roles permission);
        User build();
};

#endif //PPO_USERBUILDER_H