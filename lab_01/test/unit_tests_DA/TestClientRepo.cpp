#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
#include "../../src/business_logic/rules/ClientRules.h"
#include "../../src/business_logic/models/ModelClient.h"
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"

struct TestPgClientRepo : public testing::Test {
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

TEST_F(TestPgClientRepo, TestGetClientByID)
{
    PgClientRepository crep = PgClientRepository(*connectParams);

    Client cl = crep.getClientByID(1);

    EXPECT_EQ(cl.getID(), 1);
    EXPECT_EQ(cl.getUserID(), 4);
    EXPECT_EQ(cl.getName(), "b");
    EXPECT_EQ(cl.getSurname(), "b");
    EXPECT_EQ(cl.getPatronymic(), "b");
    EXPECT_EQ(cl.getPassportNum(), 7777912345);
}


TEST_F(TestPgClientRepo, TestGetClientsByFIO)
{
    PgClientRepository crep = PgClientRepository(*connectParams);
    std::vector<Client> clients = std::vector<Client>();

    clients = crep.getClientByFIO({.name="b", .surname="b", .patronymic="b"});

    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients[0].getID(), 1);
    EXPECT_EQ(clients[0].getUserID(), 4);
    EXPECT_EQ(clients[0].getName(), "b");
    EXPECT_EQ(clients[0].getSurname(), "b");
    EXPECT_EQ(clients[0].getPatronymic(), "b");
    EXPECT_EQ(clients[0].getPassportNum(), 7777912345);
}

TEST_F(TestPgClientRepo, TestGetAllClients)
{
    PgClientRepository crep = PgClientRepository(*connectParams);
    std::vector<Client> clients = std::vector<Client>();

    clients = crep.getAllClients();
    EXPECT_EQ(clients.size(), 2);
}

TEST_F(TestPgClientRepo, TestAddClient)
{
    PgClientRepository crep = PgClientRepository(*connectParams);

    int id = crep.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c",
     .passport_num=99999, .birth_date=1977, .address="Street 11", .email="c@mail.ru", .phone="+79183456783"});

    Client tmpClient = crep.getClientByID(id);
    EXPECT_EQ(tmpClient.getID(), id);
    EXPECT_EQ(tmpClient.getUserID(), 3);
    EXPECT_EQ(tmpClient.getPassportNum(), 99999);
}

TEST_F(TestPgClientRepo, TestUpdateClient)
{
    PgClientRepository crep = PgClientRepository(*connectParams);
    Client tmpClient = Client(3, 3, "c", "c", "c", 99999, 1977, "Street 11", "c@mail.ru", "+79183456783");
    tmpClient.setEmail("bnew@mail.ru");

    crep.updateEl(tmpClient);

    tmpClient = crep.getClientByID(3);
    EXPECT_EQ(tmpClient.getID(), 3);
    EXPECT_EQ(tmpClient.getEmail(), "bnew@mail.ru");
}

TEST_F(TestPgClientRepo, TestDeleteClient)
{
    PgClientRepository crep = PgClientRepository(*connectParams);

    crep.deleteEl(3);

    EXPECT_EQ(crep.getAllClients().size(), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
