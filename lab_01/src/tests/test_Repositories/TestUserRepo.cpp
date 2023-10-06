#include <gtest/gtest.h>

#include "../../data_access/PostgresRepositories/PgUserRepository.h"
#include "../../business_logic/rules/UserRules.h"
#include "../../business_logic/models/ModelUser.h"

TEST(TestPgUserRepo, TestGetUserIDByLogin)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgUserRepository rep = PgUserRepository(connectParams);
    UserRules urules(rep);

    int id = urules.getUserID("admin");
    ASSERT_EQ(id, 1);
}

TEST(TestPgUserRepo, TestAddandDeleteUser)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgUserRepository rep = PgUserRepository(connectParams);
    UserRules urules(rep);

    int id = urules.addUser({.login="789", .password="11111", .permission=CLIENT});
    User tmpUser = urules.getUser(id);
    EXPECT_EQ(tmpUser.getID(), id);
    EXPECT_EQ(tmpUser.getLogin(), "789");
    EXPECT_EQ(tmpUser.getPassword(), "11111");
    EXPECT_EQ(tmpUser.getUserRole(), CLIENT);
    urules.deleteUser(id);
    ASSERT_THROW(urules.getUser(id), UserNotFoundException);
}

TEST(TestPgUserRepo, TestUpdateUser)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgUserRepository rep = PgUserRepository(connectParams);
    UserRules urules(rep);

    int id = urules.addUser({.login="789", .password="11111", .permission=CLIENT});
    User tmpUser = urules.getUser(id);
    EXPECT_EQ(tmpUser.getID(), id);
    EXPECT_EQ(tmpUser.getLogin(), "789");
    EXPECT_EQ(tmpUser.getPassword(), "11111");
    EXPECT_EQ(tmpUser.getUserRole(), CLIENT);
    urules.updateUserPassword(id, "88888");
    urules.updateUserLogin(id, "790");
    urules.updateUserPermission(id, MANAGER);
    tmpUser = urules.getUser(id);
    EXPECT_EQ(tmpUser.getLogin(), "790");
    EXPECT_EQ(tmpUser.getPassword(), "88888");
    EXPECT_EQ(tmpUser.getUserRole(), MANAGER);
    urules.deleteUser(id);
    ASSERT_THROW(urules.getUser(id), UserNotFoundException);
}

TEST(TestPgUserRepo, TestGetAllUsers)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgUserRepository rep = PgUserRepository(connectParams);
    UserRules urules(rep);

    std::vector<User> users = std::vector<User>();
    users = urules.getAllUsers();
    EXPECT_EQ(users.size(), 4);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}