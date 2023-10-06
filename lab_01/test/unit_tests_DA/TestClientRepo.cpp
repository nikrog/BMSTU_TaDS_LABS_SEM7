#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
#include "../../src/business_logic/rules/ClientRules.h"
#include "../../src/business_logic/models/ModelClient.h"
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"

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
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Альфа банк', 1234, 'Москва', 'alphabank@alpha.ru', '+74953459872', 'alphabank.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Райфайзен банк', 1235, 'Москва', 'raifaizen@raif.ru', '+74953459873', 'raiffaizen.ru');");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Россельхоз банк', 6667, 'Москва', 'rosselhoz@rsb.ru', '+74953479973', 'rosselhoz.ru');");
        curConnect.exec("INSERT INTO BA.managers (user_id, bank_id) VALUES (2, 1)");
        curConnect.exec("INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES " \
        "('b', 'b', 'b', 7777912345, 19860203, 'Street 9', 'b@mail.ru', '+79183456781', 4);");
        curConnect.exec("INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES " \
        "('a', 'a', 'a', 7776933333, 19990623, 'Street 6', 'a@mail.ru', '+79183456745', 3);");
        curConnect.commit();
    }
}

struct TestPgClientRepo : public testing::Test {
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
    Client tmpClient = Client(2, 3, "a", "a", "a", 7776933333, 19990623, "Street 6", "a@mail.ru", "+79183456745");
    tmpClient.setEmail("bnew@mail.ru");

    crep.updateEl(tmpClient);

    tmpClient = crep.getClientByID(2);
    EXPECT_EQ(tmpClient.getID(), 2);
    EXPECT_EQ(tmpClient.getEmail(), "bnew@mail.ru");
}

TEST_F(TestPgClientRepo, TestDeleteClient)
{
    PgClientRepository crep = PgClientRepository(*connectParams);

    crep.deleteEl(2);

    EXPECT_EQ(crep.getAllClients().size(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
