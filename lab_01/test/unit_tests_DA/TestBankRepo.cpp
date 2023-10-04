#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"
#include "../../src/business_logic/rules/BankRules.h"
#include "../../src/business_logic/models/ModelBank.h"

struct TestPgBankRepo : public testing::Test {
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

TEST_F(TestPgBankRepo, TestGetBankByID)
{
    PgBankRepository rep = PgBankRepository(connectParams);

    Bank tmpBank = rep.getBankByID(6);

    EXPECT_EQ(tmpBank.getID(), 6);
    EXPECT_EQ(tmpBank.getLicenseNum(), 7654);
    EXPECT_EQ(tmpBank.getName(), "ВТБ");
}

TEST_F(TestPgBankRepo, TestGetBankByName)
{
    PgBankRepository rep = PgBankRepository(connectParams);

    Bank tmpBank = rep.getBankByName("ВТБ");

    EXPECT_EQ(tmpBank.getID(), 6);
    EXPECT_EQ(tmpBank.getLicenseNum(), 7654);
    EXPECT_EQ(tmpBank.getName(), "ВТБ");
}

TEST_F(TestPgBankRepo, TestGetAllBanks)
{
    PgBankRepository rep = PgBankRepository(*connectParams);
    std::vector<Bank> banks = std::vector<Bank>();

    banks = rep.getAllBanks();

    EXPECT_EQ(banks.size(), 8);
}

TEST_F(TestPgBankRepo, TestAddBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);

    int id = rep.addBank({.name="Alfa", .license_num=1236, .address="Street 54",
     .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});

    Bank tmpBank = rep.getBankByID(id);
    EXPECT_EQ(tmpBank.getID(), id);
    EXPECT_EQ(tmpBank.getLicenseNum(), 1236);
    EXPECT_EQ(tmpBank.getName(), "Alfa");
}

TEST_F(TestPgBankRepo, TestUpdateBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);
    Bank tmpBank = Bank(9, "Alfa", 1236, "Street 54","alfa@alfa.ru", "+749567890999", "alfa.ru");
    tmpBank.setAddress("Street 90");

    rep.updateEl(tmpBank);

    EXPECT_EQ(rep.getBankByID(9).getAddress(), "Street 90");
    /*brules.deleteBank(id);
    ASSERT_THROW(brules.getBank(id), BankNotFoundException);*/
}

TEST_F(TestPgBankRepo, TestDeleteBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);

    rep.deleteEl(9);

    EXPECT_EQ(rep.getAllBanks().size(), 8);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}