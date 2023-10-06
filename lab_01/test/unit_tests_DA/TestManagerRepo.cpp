#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/business_logic/rules/ManagerRules.h"
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"
#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
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
        curConnect.commit();
    }
}

struct TestPgManagerRepo : public testing::Test {
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

TEST_F(TestPgManagerRepo, TestGetManagerByID)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    Manager m = mrep.getManagerByID(1);

    EXPECT_EQ(m.getID(), 1);
    EXPECT_EQ(m.getUserID(), 2);
    EXPECT_EQ(m.getBankID(), 1);
}

TEST_F(TestPgManagerRepo, TestGetManagerByUID)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    Manager m = mrep.getManagerByUID(2);

    EXPECT_EQ(m.getID(), 1);
    EXPECT_EQ(m.getUserID(), 2);
    EXPECT_EQ(m.getBankID(), 1);
}

TEST_F(TestPgManagerRepo, TestGetManagerByBank)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    std::vector<Manager> managers = mrep.getManagerByBank(1);

    EXPECT_EQ(managers.size(), 1);
    EXPECT_EQ(managers[0].getID(), 1);
    EXPECT_EQ(managers[0].getBankID(), 1);
}

TEST_F(TestPgManagerRepo, TestGetAllManagers)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    std::vector<Manager> managers = mrep.getAllManagers();

    EXPECT_EQ(managers.size(), 1);
}

TEST_F(TestPgManagerRepo, TestAddManager)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    int id = mrep.addManager(2, 2);

    Manager tmpManager = mrep.getManagerByID(id);
    EXPECT_EQ(tmpManager.getID(), id);
    EXPECT_EQ(tmpManager.getUserID(), 2);
    EXPECT_EQ(tmpManager.getBankID(), 2);
}

TEST_F(TestPgManagerRepo, TestUpdateManager)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);
    Manager tmpManager = Manager(1, 2, 1);
    tmpManager.setBankID(3);

    mrep.updateEl(tmpManager);

    EXPECT_EQ(mrep.getManagerByID(1).getBankID(), 3);
}

TEST_F(TestPgManagerRepo, TestDeleteManager)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    mrep.deleteEl(1);

    std::vector<Manager> managers = mrep.getAllManagers();
    EXPECT_EQ(managers.size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
