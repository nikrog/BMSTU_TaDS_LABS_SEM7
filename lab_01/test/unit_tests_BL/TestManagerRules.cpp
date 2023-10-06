#include <gtest/gtest.h>
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/business_logic/rules/ManagerRules.h"
#include "../../src/data_access/MockRepositories/MockManagerRepository.h"
#include "../../src/data_access/MockRepositories/MockUserRepository.h"
#include "../../src/data_access/MockRepositories/MockBankRepository.h"
#include "../../src/data_access/MockRepositories/MockClientRepository.h"
#include "../../src/logger/Logger.h"

struct TestManagerRules : public testing::Test {
    Logger *logger;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<User> users;
    std::vector<Bank> banks;

    void SetUp() 
    {
        logger = new Logger("log_file.txt", FATAL);
        managers.push_back(Manager(1, 1, 1));
        managers.push_back(Manager(2, 2, 2));
        managers.push_back(Manager(3, 5, 2));
        users.push_back(User(1, "abc", "11111", MANAGER));
        users.push_back(User(2, "abd", "11112", MANAGER));
        users.push_back(User(3, "abe", "11113", CLIENT));
        users.push_back(User(4, "abf", "11114", CLIENT));
        users.push_back(User(5, "abg", "11114", MANAGER));
        clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
        clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
        banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
        banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    }
    void TearDown() 
    { 
        delete logger;
    }
};

TEST_F(TestManagerRules, TestGetManagerPositive)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    Manager tmpManager = mrules.getManager(2);

    EXPECT_EQ(tmpManager.getID(), 2);
    EXPECT_EQ(tmpManager.getUserID(), 2);
    EXPECT_EQ(tmpManager.getBankID(), 2);
}

TEST_F(TestManagerRules, TestGetManagerNegative)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.getManager(4), ManagerNotFoundException);
}

TEST_F(TestManagerRules, TestGetAllManagers)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    managers = mrules.getAllManagers();

    EXPECT_EQ(managers.size(), 3);
    EXPECT_EQ(managers[0].getID(), 1);
    EXPECT_EQ(managers[1].getID(), 2);
    EXPECT_EQ(managers[2].getID(), 3);
}

TEST_F(TestManagerRules, TestGetManagersByBankPositive)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    managers = mrules.getManagerByBank(2);

    EXPECT_EQ(managers.size(), 2);
    EXPECT_EQ(managers[0].getID(), 2);
    EXPECT_EQ(managers[1].getID(), 3);
}

TEST_F(TestManagerRules, TestDeleteManagerPositive)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    mrules.deleteManager(2);

    ASSERT_THROW(mrules.getManager(2), ManagerNotFoundException);
}

TEST_F(TestManagerRules, TestDeleteManagerNegative)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.deleteManager(4), ManagerNotFoundException);
}

TEST_F(TestManagerRules, TestAddManagerPositive)
{
    managers.erase(managers.end() - 1);
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    int id = mrules.addManager(5, 2);

    EXPECT_EQ(mrules.getManager(id).getID(), id);
    EXPECT_EQ(mrules.getManager(id).getUserID(), 5);
    EXPECT_EQ(mrules.getManager(id).getBankID(), 2);
}

TEST_F(TestManagerRules, TestAddManagerNegativeNonExistentUser)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.addManager(6, 2), UserNotFoundException);
}

TEST_F(TestManagerRules, TestAddManagerNegativeNonExistentBank)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.addManager(5, 3), BankNotFoundException);
}

TEST_F(TestManagerRules, TestUpdateManagerPositive)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    mrules.updateManagerBank(2, 1);

    EXPECT_EQ(mrules.getManager(2).getID(), 2);
    EXPECT_EQ(mrules.getManager(2).getBankID(), 1);
}


TEST_F(TestManagerRules, TestUpdateManagerNegativeNotExistentBank)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.updateManagerBank(2, 3), BankNotFoundException);
}

TEST_F(TestManagerRules, TestUpdateManagerNegativeNotExistentManager)
{
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository, *logger);

    ASSERT_THROW(mrules.updateManagerBank(4, 2), ManagerNotFoundException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}