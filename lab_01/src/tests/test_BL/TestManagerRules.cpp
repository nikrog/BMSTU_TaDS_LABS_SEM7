#include <gtest/gtest.h>
#include "../../business_logic/models/ModelManager.h"
#include "../../business_logic/rules/ManagerRules.h"
#include "../../data_access/MockRepositories/MockManagerRepository.h"
#include "../../data_access/MockRepositories/MockUserRepository.h"
#include "../../data_access/MockRepositories/MockBankRepository.h"
#include "../../data_access/MockRepositories/MockClientRepository.h"

TEST(TestMangerRules, TestGetManagerPositive)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    Manager tmpManager = mrules.getManager(2);
    EXPECT_EQ(tmpManager.getID(), 2);
    EXPECT_EQ(tmpManager.getUserID(), 2);
    EXPECT_EQ(tmpManager.getBankID(), 2);
}

TEST(TestMangerRules, TestGetManagerNegative)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.getManager(3), ManagerNotFoundException);
}

TEST(TestMangerRules, TestGetAllManagers)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    managers = mrules.getAllManagers();
    EXPECT_EQ(managers.size(), 2);
    EXPECT_EQ(managers[0].getID(), 1);
    EXPECT_EQ(managers[1].getID(), 2);
}

TEST(TestMangerRules, TestGetManagersByBankPositive)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    managers.push_back(Manager(3, 5, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", MANAGER));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    managers = mrules.getManagerByBank(2);
    EXPECT_EQ(managers.size(), 2);
    EXPECT_EQ(managers[0].getID(), 2);
    EXPECT_EQ(managers[1].getID(), 3);
}

TEST(TestMangerRules, TestDeleteManagerPositive)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    managers.push_back(Manager(3, 5, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", MANAGER));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    mrules.deleteManager(2);
    ASSERT_THROW(mrules.getManager(2), ManagerNotFoundException);
}

TEST(TestMangerRules, TestDeleteManagerNegative)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    managers.push_back(Manager(3, 5, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", MANAGER));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.deleteManager(4), ManagerNotFoundException);
}

TEST(TestMangerRules, TestAddManagerPositive)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    int id = mrules.addManager(5, 2);
    Manager tmpManager = mrules.getManager(id);
    EXPECT_EQ(tmpManager.getID(), id);
    EXPECT_EQ(tmpManager.getUserID(), 5);
    EXPECT_EQ(tmpManager.getBankID(), 2);
}

TEST(TestMangerRules, TestAddManagerNegativeNonExistentUser)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.addManager(6, 2), UserNotFoundException);
}

TEST(TestMangerRules, TestAddManagerNegativeNonExistentBank)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.addManager(5, 3), BankNotFoundException);
}

TEST(TestMangerRules, TestUpdateManagerPositive)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    mrules.updateManagerBank(2, 1);
    Manager tmpManager = mrules.getManager(2);
    EXPECT_EQ(tmpManager.getID(), 2);
    EXPECT_EQ(tmpManager.getBankID(), 1);
}


TEST(TestMangerRules, TestUpdateManagerNegativeNotExistentBank)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.updateManagerBank(2, 3), BankNotFoundException);
}

TEST(TestMangerRules, TestUpdateManagerNegativeNotExistentManager)
{
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Bank> banks;
    std::vector<User> users;
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
    banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
    MockManagerRepository managerRepository(managers);
    MockBankRepository bankRepository(banks);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    ManagerRules mrules(managerRepository, bankRepository, userRepository, clientRepository);
    ASSERT_THROW(mrules.updateManagerBank(3, 2), ManagerNotFoundException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}