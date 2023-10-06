#include <gtest/gtest.h>
#include "../../business_logic/models/ModelBank.h"
#include "../../business_logic/rules/BankRules.h"
#include "../../data_access/MockRepositories/MockBankRepository.h"


TEST(TestBankRules, TestGetBankPositive)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
Bank tmpBank = brules.getBank(2);
EXPECT_EQ(tmpBank.getID(), 2);
EXPECT_EQ(tmpBank.getName(), "Sber");
EXPECT_EQ(tmpBank.getLicenseNum(), 1235);
EXPECT_EQ(tmpBank.getAddress(), "Street 78");
EXPECT_EQ(tmpBank.getEmail(), "sber@sber.ru");
EXPECT_EQ(tmpBank.getPhone(), "+749567890777");
EXPECT_EQ(tmpBank.getWebsite(), "sber.ru");
}

TEST(TestBankRules, TestGetBankNegativeNotFound)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
ASSERT_THROW(brules.getBank(3), BankNotFoundException);
}

TEST(TestBankRules, TestGetBankByNamePositive)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
Bank tmpBank = brules.getBankByName("Sber");
EXPECT_EQ(tmpBank.getID(), 2);
EXPECT_EQ(tmpBank.getName(), "Sber");
EXPECT_EQ(tmpBank.getLicenseNum(), 1235);
EXPECT_EQ(tmpBank.getAddress(), "Street 78");
EXPECT_EQ(tmpBank.getEmail(), "sber@sber.ru");
EXPECT_EQ(tmpBank.getPhone(), "+749567890777");
EXPECT_EQ(tmpBank.getWebsite(), "sber.ru");
}

TEST(TestBankRules, TestGetBankByNameNegativeNotFound)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
ASSERT_THROW(brules.getBankByName("VTB2"), BankNotFoundException);
}

TEST(TestBankRules, TestGetAllBanks)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
banks = brules.getAllBanks();
EXPECT_EQ(banks.size(), 2);
EXPECT_EQ(banks[0].getName(), "VTB");
EXPECT_EQ(banks[1].getName(), "Sber");
}

TEST(TestBankRules, TestDeleteBankPositive)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
brules.deleteBank(2);
ASSERT_THROW(brules.getBank(2), BankNotFoundException);
}

TEST(TestBankRules, TestDeleteBankNegative)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
ASSERT_THROW(brules.deleteBank(3), BankNotFoundException);
}

TEST(TestBankRules, TestAddBankPositive)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
int id = brules.addBank({.name="Alfa", .license_num=1236, .address="Street 54", .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});
Bank tmpBank = brules.getBank(id);
EXPECT_EQ(tmpBank.getID(), id);
EXPECT_EQ(tmpBank.getLicenseNum(), 1236);
EXPECT_EQ(tmpBank.getName(), "Alfa");
}

TEST(TestBankRules, TestAddBankNegativeEmptyName)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
ASSERT_THROW(brules.addBank({.name="", .license_num=1236, .address="Street 54", .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"}),
 BankAddErrorException);
}

TEST(TestBankRules, TestAddBankNegativeIncorrectLicense)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
ASSERT_THROW(brules.addBank({.name="", .license_num=-1236, .address="Street 54", .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"}),
 BankAddErrorException);
}

TEST(TestBankRules, TestUpdateBankPositive)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
Bank tmpBank = brules.getBank(2);
tmpBank.setAddress("Street 90");
brules.updateBank(tmpBank);
tmpBank = brules.getBank(2);
EXPECT_EQ(tmpBank.getAddress(), "Street 90");
}


TEST(TestBankRules, TestUpdateBankNegativeEmptyName)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
Bank tmpBank = brules.getBank(2);
tmpBank.setName("");
ASSERT_THROW(brules.updateBank(tmpBank), BankUpdateErrorException);
}

TEST(TestBankRules, TestUpdateBankNegativeIncorrectLicense)
{
std::vector<Bank> banks;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
MockBankRepository bankRepository(banks);
BankRules brules(bankRepository);
Bank tmpBank = brules.getBank(2);
tmpBank.setLicenseNum(-1);
ASSERT_THROW(brules.updateBank(tmpBank), BankUpdateErrorException);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}