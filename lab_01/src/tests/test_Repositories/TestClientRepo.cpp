#include <gtest/gtest.h>

#include "../../data_access/PostgresRepositories/PgClientRepository.h"
#include "../../business_logic/rules/ClientRules.h"
#include "../../business_logic/models/ModelClient.h"
#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/models/ModelManager.h"
#include "../../data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../data_access/PostgresRepositories/PgUserRepository.h"

TEST(TestPgClientRepo, TestClientsByFIO)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    ClientRules crules(crep, urep, mrep);
    std::vector<Client> clients = std::vector<Client>();
    clients = crules.getClientByFIO({.name="b", .surname="b", .patronymic="b"});
    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients[0].getID(), 1);
    EXPECT_EQ(clients[0].getUserID(), 4);
    EXPECT_EQ(clients[0].getName(), "b");
    EXPECT_EQ(clients[0].getSurname(), "b");
    EXPECT_EQ(clients[0].getPatronymic(), "b");
    EXPECT_EQ(clients[0].getPassportNum(), 77779);
}

TEST(TestPgClientRepo, TestAddandDeleteClient)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    ClientRules crules(crep, urep, mrep);

    int id = crules.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c",
     .passport_num=99999, .birth_date=1977, .address="Street 11", .email="c@mail.ru", .phone="+79183456783"});
    Client tmpClient = crules.getClient(id);
    EXPECT_EQ(tmpClient.getID(), id);
    EXPECT_EQ(tmpClient.getUserID(), 3);
    EXPECT_EQ(tmpClient.getPassportNum(), 99999);
    crules.deleteClient(id);
    ASSERT_THROW(crules.getClient(id), ClientNotFoundException);
}

TEST(TestPgClientRepo, TestUpdateClient)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    ClientRules crules(crep, urep, mrep);

    int id = crules.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c",
     .passport_num=99999, .birth_date=1977, .address="Street 11", .email="c@mail.ru", .phone="+79183456783"});
    Client tmpClient = crules.getClient(id);
    EXPECT_EQ(tmpClient.getID(), id);
    EXPECT_EQ(tmpClient.getUserID(), 3);
    EXPECT_EQ(tmpClient.getPassportNum(), 99999);
    tmpClient = crules.getClient(id);
    tmpClient.setEmail("bnew@mail.ru");
    crules.updateClient(tmpClient);
    EXPECT_EQ(tmpClient.getID(), id);
    EXPECT_EQ(tmpClient.getEmail(), "bnew@mail.ru");
    crules.deleteClient(id);
    ASSERT_THROW(crules.getClient(id), ClientNotFoundException);
}

TEST(TestPgClientRepo, TestGetAllClients)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    ClientRules crules(crep, urep, mrep);

    int id = crules.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c",
     .passport_num=99999, .birth_date=1977, .address="Street 11", .email="c@mail.ru", .phone="+79183456783"});

    std::vector<Client> clients = std::vector<Client>();
    clients = crules.getAllClients();
    EXPECT_EQ(clients.size(), 2);

    crules.deleteClient(id);
    ASSERT_THROW(crules.getClient(id), ClientNotFoundException);

    clients = crules.getAllClients();
    EXPECT_EQ(clients.size(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
