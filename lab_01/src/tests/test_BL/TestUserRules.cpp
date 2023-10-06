#include <gtest/gtest.h>
#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/rules/UserRules.h"
#include "../../data_access/MockRepositories/MockUserRepository.h"


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

TEST(TestUserRules, TestAddUserIncorrectPasswordShort)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.addUser({.login="789", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestAddUserIncorrectLoginEmpty)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.addUser({.login="", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestAddUserIncorrectLoginDuplicate)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.addUser({.login="abc", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestDeleteUserPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
urules.deleteUser(1);
ASSERT_THROW(urules.getUser(1), UserNotFoundException);
}

TEST(TestUserRules, TestDeleteUserNegative)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.deleteUser(2), UserNotFoundException);
}

TEST(TestUserRules, TestGetAllUsers)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
users = urules.getAllUsers();
EXPECT_EQ(users.size(), 2);
}

TEST(TestUserRules, TestGetUserIDPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
int id = urules.getUserID("def");
EXPECT_EQ(id, 2);
}

TEST(TestUserRules, TestGetUserIDNegativeNotFound)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.getUserID("ghk"), UserNotFoundException);
}

TEST(TestUserRules, TestUpdateUserLoginPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
urules.updateUserLogin(2, "ghk");
User tmpUser = urules.getUser(2);
EXPECT_EQ(tmpUser.getLogin(), "ghk");
}

TEST(TestUserRules, TestUpdateUserPasswordPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
urules.updateUserPassword(2, "88888");
User tmpUser = urules.getUser(2);
EXPECT_EQ(tmpUser.getPassword(), "88888");
}

TEST(TestUserRules, TestUpdateUserPermissionPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
urules.updateUserPermission(2, MANAGER);
User tmpUser = urules.getUser(2);
EXPECT_EQ(tmpUser.getUserRole(), MANAGER);
}

TEST(TestUserRules, TestUpdateUserNegativeNotFound)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.updateUserLogin(3, "ghk"), UserNotFoundException);
}

TEST(TestUserRules, TestUpdateUserNegativeShortPassword)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.updateUserPassword(2, "ghk"), UserUpdateErrorException);
}

TEST(TestUserRules, TestUpdateUserNegativeExistedLogin)
{
std::vector<User> users;
users.push_back(User(1, "login", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.updateUserLogin(2, "login"), UserUpdateErrorException);
}

TEST(TestUserRules, TestGetUserPositive)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
User tmpUser = urules.getUser(2);
EXPECT_EQ(tmpUser.getID(), 2);
EXPECT_EQ(tmpUser.getLogin(), "def");
EXPECT_EQ(tmpUser.getPassword(), "11112");
EXPECT_EQ(tmpUser.getUserRole(), CLIENT);
}

TEST(TestUserRules, TestGetUserNegativeNotFound)
{
std::vector<User> users;
users.push_back(User(1, "abc", "11112", CLIENT));
users.push_back(User(2, "def", "11112", CLIENT));
MockUserRepository userRepository(users);
UserRules urules(userRepository);
ASSERT_THROW(urules.getUser(3), UserNotFoundException);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}