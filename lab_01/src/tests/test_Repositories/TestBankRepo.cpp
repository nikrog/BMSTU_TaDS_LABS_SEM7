#include <gtest/gtest.h>

#include "../../data_access/PostgresRepositories/PgBankRepository.h"
#include "../../business_logic/rules/BankRules.h"
#include "../../business_logic/models/ModelBank.h"

TEST(TestPgBankRepo, TestGetBankByName)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgBankRepository rep = PgBankRepository(connectParams);
    BankRules brules(rep);
    Bank tmpBank = brules.getBankByName("test2");
    EXPECT_EQ(tmpBank.getID(), 1);
    EXPECT_EQ(tmpBank.getLicenseNum(), 1234);
    EXPECT_EQ(tmpBank.getName(), "test2");
}

TEST(TestPgBankRepo, TestAddandDeleteBank)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgBankRepository rep = PgBankRepository(connectParams);
    BankRules brules(rep);
    int id = brules.addBank({.name="Alfa", .license_num=1236, .address="Street 54",
     .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});
    Bank tmpBank = brules.getBank(id);
    EXPECT_EQ(tmpBank.getID(), id);
    EXPECT_EQ(tmpBank.getLicenseNum(), 1236);
    EXPECT_EQ(tmpBank.getName(), "Alfa");
    brules.deleteBank(id);
    ASSERT_THROW(brules.getBank(id), BankNotFoundException);
}

TEST(TestPgBankRepo, TestUpdateBank)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgBankRepository rep = PgBankRepository(connectParams);
    BankRules brules(rep);
    int id = brules.addBank({.name="Alfa", .license_num=1236, .address="Street 54",
     .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});
    Bank tmpBank = brules.getBank(id);
    EXPECT_EQ(tmpBank.getID(), id);
    EXPECT_EQ(tmpBank.getLicenseNum(), 1236);
    EXPECT_EQ(tmpBank.getName(), "Alfa");
    tmpBank.setAddress("Street 90");
    brules.updateBank(tmpBank);
    tmpBank = brules.getBank(id);
    EXPECT_EQ(tmpBank.getAddress(), "Street 90");
    brules.deleteBank(id);
    ASSERT_THROW(brules.getBank(id), BankNotFoundException);
}

TEST(TestPgBankRepo, TestGetAllBanks)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgBankRepository rep = PgBankRepository(connectParams);
    BankRules brules(rep);

    std::vector<Bank> banks = std::vector<Bank>();
    banks = brules.getAllBanks();
    EXPECT_EQ(banks.size(), 2);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}