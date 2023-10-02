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

struct TestUserRules : public testing::Test {
  Logger *logger;

  void SetUp() {logger = new Logger("log_file.txt", FATAL);}
  void TearDown() { delete logger; }
};

TEST_F(TestUserRules, TestAddUserPositive)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);
  
    EXPECT_CALL(userRepository, getAllUsers()).Times(1);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(userRepository, getUserByID(1)).Times(1).WillOnce(testing::Return(UserOM().client(1).withLogin( \
        "789").withPassword("11111").build()));

    urules.addUser({.login="789", .password="11111", .permission=CLIENT});
}

TEST_F(TestUserRules, TestAddUserIncorrectPasswordShort)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(0);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="789", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST_F(TestUserRules, TestAddUserIncorrectLoginEmpty)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(0);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="", .password="111", .permission=CLIENT}), UserAddErrorException);
}

TEST_F(TestUserRules, TestAddUserIncorrectLoginDuplicate)
{
    std::vector<User> users;
    users.push_back(UserOM().client(1).withLogin("abc").build());
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(1).WillOnce(testing::Return(users));
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);
    EXPECT_CALL(userRepository, getUserByID(1)).Times(0);

    ASSERT_THROW(urules.addUser({.login="abc", .password="111111", .permission=CLIENT}), UserAddErrorException);
}

TEST_F(TestUserRules, TestDeleteUserPositive)
{

    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(1)).Times(1).WillOnce(testing::Return(UserOM().client(1).withLogin( \
        "789").withPassword("11111").build()));
    EXPECT_CALL(userRepository, deleteEl(testing::_)).Times(1);

    urules.deleteUser(1);
}

TEST_F(TestUserRules, TestDeleteUserNegative)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1);
    EXPECT_CALL(userRepository, addUser(testing::_)).Times(0);

    ASSERT_THROW(urules.deleteUser(2), UserNotFoundException);
}

TEST_F(TestUserRules, TestGetAllUsers)
{
    std::vector<User> users;
    users.push_back(UserOM().manager(1).build());
    users.push_back(UserOM().client(2).build());
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getAllUsers()).Times(1).WillOnce(testing::Return(users));

    users = urules.getAllUsers();

    EXPECT_EQ(users.size(), 2);
}

TEST_F(TestUserRules, TestGetUserIDPositive)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserID("def")).Times(1).WillOnce(testing::Return(2));

    int id = urules.getUserID("def");
}

TEST_F(TestUserRules, TestGetUserIDNegativeNotFound)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserID("ghk")).Times(1).WillOnce(testing::Return(NONE));
    ASSERT_THROW(urules.getUserID("ghk"), UserNotFoundException);
}

TEST_F(TestUserRules, TestUpdateUserLoginPositive)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(UserOM().client(2).withLogin("ghk").build()));
    EXPECT_CALL(userRepository, getAllUsers()).Times(1);
    EXPECT_CALL(userRepository, updateEl(testing::_)).Times(1);

    urules.updateUserLogin(2, "ghk");
}

TEST_F(TestUserRules, TestUpdateUserPasswordPositive)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(UserOM().client(2).withPassword("88888").build()));
    EXPECT_CALL(userRepository, updateEl(testing::_)).Times(1);

    urules.updateUserPassword(2, "88888");
}

TEST_F(TestUserRules, TestUpdateUserPermissionPositive)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(UserOM().manager(2).build()));
    EXPECT_CALL(userRepository, updateEl(testing::_)).Times(1);

    urules.updateUserPermission(2, MANAGER);
}

TEST_F(TestUserRules, TestUpdateUserNegativeNotFound)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(3)).Times(1);

    ASSERT_THROW(urules.updateUserLogin(3, "ghk"), UserNotFoundException);
}

TEST_F(TestUserRules, TestUpdateUserNegativeShortPassword)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(UserOM().manager(2).build()));

    ASSERT_THROW(urules.updateUserPassword(2, "ghk"), UserUpdateErrorException);
}

TEST_F(TestUserRules, TestUpdateUserNegativeExistedLogin)
{
    std::vector<User> users;
    users.push_back(UserOM().manager(1).withLogin("login").build());
    users.push_back(UserOM().client(2).build());
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(users.at(1)));
    EXPECT_CALL(userRepository, getAllUsers()).Times(1).WillOnce(testing::Return(users));
    EXPECT_CALL(userRepository, updateEl(testing::_)).Times(0);

    ASSERT_THROW(urules.updateUserLogin(2, "login"), UserUpdateErrorException);
}

TEST_F(TestUserRules, TestGetUserPositive)
{
    std::vector<User> users;
    users.push_back(UserOM().manager(1).withLogin("login").build());
    users.push_back(UserOM().client(2).build());
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(2)).Times(1).WillOnce(testing::Return(users.at(1)));

    urules.getUser(2);
}

TEST_F(TestUserRules, TestGetUserNegativeNotFound)
{
    MockUser userRepository = MockUser();
    UserRules urules(userRepository, *logger);

    EXPECT_CALL(userRepository, getUserByID(1)).Times(1).WillOnce(testing::Return(User()));

    ASSERT_THROW(urules.getUser(1), UserNotFoundException);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}