#include <gtest/gtest.h>
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/rules/UserRules.h"
#include "../../src/data_access/MockRepositories/MockUserRepository.h"

TEST(TestUserRules, TestAddUserPositive)
{
    std::vector<User> users;
    users.push_back(User(1, "abc", "11112", CLIENT));
    MockUserRepository userRepository(users);
    UserRules urules(userRepository);
    int id = urules.addUser({.login="789", .password="11111", .permission=CLIENT});
    User usr = urules.getUser(id);
    EXPECT_EQ(usr.getID(), id);
    EXPECT_EQ(usr.getLogin(), "789");
    EXPECT_EQ(usr.getPassword(), "11111");
    EXPECT_EQ(usr.getUserRole(), CLIENT);
}