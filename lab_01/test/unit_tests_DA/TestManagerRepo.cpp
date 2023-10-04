#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/business_logic/rules/ManagerRules.h"
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"
#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"

struct TestPgManagerRepo : public testing::Test {
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
    Manager tmpManager = Manager(2, 2, 2);
    tmpManager.setBankID(3);

    mrep.updateEl(tmpManager);

    EXPECT_EQ(mrep.getManagerByID(2).getBankID(), 3);
}

TEST_F(TestPgManagerRepo, TestDeleteManager)
{
    PgManagerRepository mrep = PgManagerRepository(*connectParams);

    mrep.deleteEl(2);

    std::vector<Manager> managers = mrep.getAllManagers();
    EXPECT_EQ(managers.size(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
