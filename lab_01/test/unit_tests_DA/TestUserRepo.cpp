#include <gtest/gtest.h>
#include <stdio.h>
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"
#include "../../src/business_logic/models/ModelUser.h"

struct TestPgUserRepo : public testing::Test {
    ConnectionParams *connectParams;

    void SetUp() 
    {
        connectParams = new ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    }
    void TearDown() 
    { 
        delete connectParams;
    }
};

TEST_F(TestPgUserRepo, TestGetUserID)
{
    //Arrange
    PgUserRepository rep = PgUserRepository(*connectParams);

    //Act
    int id = rep.getUserID("admin");

    //Assert
    ASSERT_EQ(id, 1);
}


TEST_F(TestPgUserRepo, TestGetUserByID)
{
    PgUserRepository rep = PgUserRepository(*connectParams);

    User tmpUser = rep.getUserByID(3);

    ASSERT_EQ(tmpUser.getID(), 3);
    ASSERT_EQ(tmpUser.getLogin(), "client");
    ASSERT_EQ(tmpUser.getPassword(), "22221");
    ASSERT_EQ(tmpUser.getUserRole(), CLIENT);
}


TEST_F(TestPgUserRepo, TestGetUserByLogin)
{
    PgUserRepository rep = PgUserRepository(*connectParams);

    User tmpUser = rep.getUserByLogin("client2");

    ASSERT_EQ(tmpUser.getID(), 4);
    ASSERT_EQ(tmpUser.getLogin(), "client2");
    ASSERT_EQ(tmpUser.getPassword(), "22222");
    ASSERT_EQ(tmpUser.getUserRole(), CLIENT);
}

TEST_F(TestPgUserRepo, TestAddUser)
{
    PgUserRepository rep = PgUserRepository(*connectParams);

    int id = rep.addUser({.login="789", .password="11111", .permission=CLIENT});

    User tmpUser = rep.getUserByID(id);
    EXPECT_EQ(tmpUser.getID(), id);
    EXPECT_EQ(tmpUser.getLogin(), "789");
    EXPECT_EQ(tmpUser.getPassword(), "11111");
    EXPECT_EQ(tmpUser.getUserRole(), CLIENT);
}

TEST_F(TestPgUserRepo, TestDeleteUser)
{
    PgUserRepository rep = PgUserRepository(*connectParams);

    rep.deleteEl(5);

    EXPECT_EQ(rep.getAllUsers().size(), 4);
}

TEST_F(TestPgUserRepo, TestGetAllUsers)
{
    PgUserRepository rep = PgUserRepository(*connectParams);
    std::vector<User> users = std::vector<User>();

    users = rep.getAllUsers();

    EXPECT_EQ(users.size(), 4);
}

TEST_F(TestPgUserRepo, TestUpdateUser)
{
    PgUserRepository rep = PgUserRepository(*connectParams);
    User tmpUser = User(1, "man", "22220", MANAGER);

    rep.updateEl(tmpUser);

    tmpUser = rep.getUserByID(1);
    EXPECT_EQ(tmpUser.getLogin(), "man");
    EXPECT_EQ(tmpUser.getPassword(), "22220");
    EXPECT_EQ(tmpUser.getUserRole(), MANAGER);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}