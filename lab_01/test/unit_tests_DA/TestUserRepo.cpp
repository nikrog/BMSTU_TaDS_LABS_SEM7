#include <gtest/gtest.h>
#include <stdio.h>
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"
#include "../../src/business_logic/models/ModelUser.h"

void load_data(ConnectionParams params)
{   
    std::string connect_str = params.getString();
    std::shared_ptr<pqxx::connection> connection = std::make_shared<pqxx::connection>(connect_str.c_str());

    if (connection->is_open())
    {
        //std::string sql = PostgreSQLGetUserID().get_str(login);
        pqxx::work curConnect(*connection);
        curConnect.exec("TRUNCATE TABLE BA.requests RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.products RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.clients RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.managers RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.banks RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.users RESTART IDENTITY CASCADE;");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('admin', 'admin', 3);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('manager', '11111', 2);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('client', '22221', 1);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('client2', '22222', 1);");
        /*if (result.size() == 1)
            res_id = result[0][0].as<int>();*/
        curConnect.commit();
    }
}

struct TestPgUserRepo : public testing::Test {
    ConnectionParams *connectParams;

    void SetUp() 
    {
        connectParams = new ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
        load_data(*connectParams);
    }
    void TearDown() 
    { 
        delete connectParams;
    }
};

TEST_F(TestPgUserRepo, TestGetUserID)
{
    //load_data(*connectParams);
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

    rep.deleteEl(4);

    EXPECT_EQ(rep.getAllUsers().size(), 3);
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