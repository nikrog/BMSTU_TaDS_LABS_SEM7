#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/rules/UserRules.h"
#include "../../src/data_access/MockRepositories/MockUserRepository.h"
#include "../../src/business_logic/IRepositories/IUserRepository.h"
#include "../builders/UserOM.h"
#include "../../src/logger/Logger.h"

class MockUser : public IUserRepository{
public:
    MockUser(): IUserRepository(){

    }
    ~MockUser()
    {};
    MOCK_METHOD(int, getUserID, (std::string login), (override));
    MOCK_METHOD(User, getUserByID, (int id), (override));
    MOCK_METHOD(User, getUserByLogin, (std::string login), (override));
    MOCK_METHOD(int, addUser, (UserInfo inf), (override));
    MOCK_METHOD(void, deleteEl, (int id), (override));
    MOCK_METHOD(void, updateEl, (User user_el), (override));
    MOCK_METHOD(std::vector<User>, getAllUsers, (), (override));
    MOCK_METHOD(void, setRole, (Roles role), (override));
};

TEST(TestUserRules, TestAddUserPositive)
{
    MockUser userRepository = MockUser();
    Logger logger = Logger("log_file.txt", FATAL);
    UserRules urules(userRepository, logger);
  
    EXPECT_CALL(userRepository, getAllUsers()).Times(1);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(userRepository, getUserByID(1)).Times(1).WillOnce(testing::Return(UserOM().client(1).withLogin( \
        "789").withPassword("11111").build()));

    urules.addUser({.login="789", .password="11111", .permission=CLIENT});
}

TEST(TestUserRules, TestAddUserIncorrectPasswordShort)
{
    MockUser userRepository = MockUser();
    Logger logger = Logger("log_file.txt", FATAL);
    UserRules urules(userRepository, logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(0);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="789", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestAddUserIncorrectLoginEmpty)
{
    MockUser userRepository = MockUser();
    Logger logger = Logger("log_file.txt", FATAL);
    UserRules urules(userRepository, logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(0);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestAddUserIncorrectLoginDuplicate)
{
    std::vector<User> users;
    users.push_back(UserOM().client(1).withLogin("abc").build());
    MockUser userRepository = MockUser();
    Logger logger = Logger("log_file.txt", FATAL);
    UserRules urules(userRepository, logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(1).WillOnce(testing::Return(users));
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="abc", .password="111111", .permission=CLIENT}), UserAddErrorException);
}

TEST(TestUserRules, TestDeleteUserPositive)
{

    MockUser userRepository = MockUser();
    Logger logger = Logger("log_file.txt", FATAL);
    UserRules urules(userRepository, logger);

    EXPECT_CALL(userRepository, getUserByID(1)).Times(2).WillOnce(testing::Return(UserOM().client(1).withLogin( \
        "789").withPassword("11111").build()));
    EXPECT_CALL(userRepository, deleteEl(testing::_)).Times(1);

    urules.deleteUser(1);
}

/*TEST(TestUserRules, TestDeleteUserNegative)
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
}*/


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}