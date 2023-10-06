#include <gtest/gtest.h>
#include "../../src/business_logic/models/ModelBank.h"
#include "../../src/business_logic/rules/BankRules.h"
#include "../../src/data_access/MockRepositories/MockBankRepository.h"
#include "../stub/BankStub.h"
#include "../../src/logger/Logger.h"

struct TestBankRules : public testing::Test {
  Logger *logger;

  void SetUp() {logger = new Logger("log_file.txt", FATAL);}
  void TearDown() { delete logger; }
};


TEST_F(TestBankRules, TestGetBankPositive)
{
// Arrange
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

// Act
Bank tmpBank = brules.getBank(2);

// Assert
EXPECT_EQ(tmpBank.getID(), 2);
EXPECT_EQ(tmpBank.getName(), "Sber");
EXPECT_EQ(tmpBank.getLicenseNum(), 1235);
EXPECT_EQ(tmpBank.getAddress(), "Street 78");
EXPECT_EQ(tmpBank.getEmail(), "sber@sber.ru");
EXPECT_EQ(tmpBank.getPhone(), "+749567890777");
EXPECT_EQ(tmpBank.getWebsite(), "sber.ru");
}

TEST_F(TestBankRules, TestGetBankNegativeNotFound)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

ASSERT_THROW(brules.getBank(3), BankNotFoundException);
}

TEST_F(TestBankRules, TestGetBankByNamePositive)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

Bank tmpBank = brules.getBankByName("Sber");

EXPECT_EQ(tmpBank.getID(), 2);
EXPECT_EQ(tmpBank.getName(), "Sber");
EXPECT_EQ(tmpBank.getLicenseNum(), 1235);
EXPECT_EQ(tmpBank.getAddress(), "Street 78");
EXPECT_EQ(tmpBank.getEmail(), "sber@sber.ru");
EXPECT_EQ(tmpBank.getPhone(), "+749567890777");
EXPECT_EQ(tmpBank.getWebsite(), "sber.ru");
}

TEST_F(TestBankRules, TestGetBankByNameNegativeNotFound)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

ASSERT_THROW(brules.getBankByName("VTB2"), BankNotFoundException);
}

TEST_F(TestBankRules, TestGetAllBanks)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

std::vector<Bank> banks = brules.getAllBanks();

EXPECT_EQ(banks.size(), 2);
EXPECT_EQ(banks[0].getName(), "VTB");
EXPECT_EQ(banks[1].getName(), "Sber");
}

TEST_F(TestBankRules, TestDeleteBankPositive)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

brules.deleteBank(2);

ASSERT_THROW(brules.getBank(2), BankNotFoundException);
}

TEST_F(TestBankRules, TestDeleteBankNegative)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

ASSERT_THROW(brules.deleteBank(3), BankNotFoundException);
}

TEST_F(TestBankRules, TestAddBankPositive)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

int id = brules.addBank({.name="Alfa", .license_num=1236, .address="Street 54",
 .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});

EXPECT_EQ(brules.getBank(id).getID(), id);
EXPECT_EQ(brules.getBank(id).getLicenseNum(), 1236);
EXPECT_EQ(brules.getBank(id).getName(), "Alfa");
}

TEST_F(TestBankRules, TestAddBankNegativeEmptyName)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

ASSERT_THROW(brules.addBank({.name="", .license_num=1236, .address="Street 54", .email="alfa@alfa.ru",
 .phone="+749567890999", .website="alfa.ru"}), BankAddErrorException);
}

TEST_F(TestBankRules, TestAddBankNegativeIncorrectLicense)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);

ASSERT_THROW(brules.addBank({.name="", .license_num=-1236, .address="Street 54", .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"}),
 BankAddErrorException);
}

TEST_F(TestBankRules, TestUpdateBankPositive)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);
Bank tmpBank = brules.getBank(2);
tmpBank.setAddress("Street 90");

brules.updateBank(tmpBank);

EXPECT_EQ(brules.getBank(2).getAddress(), "Street 90");
}


TEST_F(TestBankRules, TestUpdateBankNegativeEmptyName)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);
Bank tmpBank = brules.getBank(2);
tmpBank.setName("");

ASSERT_THROW(brules.updateBank(tmpBank), BankUpdateErrorException);
}

TEST_F(TestBankRules, TestUpdateBankNegativeIncorrectLicense)
{
BankStub bankRepository = BankStub();
BankRules brules(bankRepository, *logger);
Bank tmpBank = brules.getBank(2);
tmpBank.setLicenseNum(-1);

ASSERT_THROW(brules.updateBank(tmpBank), BankUpdateErrorException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}