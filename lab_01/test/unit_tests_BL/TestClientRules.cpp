#include <gtest/gtest.h>
#include "../../src/business_logic/models/ModelClient.h"
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/business_logic/rules/ClientRules.h"
#include "../../src/data_access/MockRepositories/MockClientRepository.h"
#include "../../src/data_access/MockRepositories/MockUserRepository.h"
#include "../../src/data_access/MockRepositories/MockManagerRepository.h"
#include "../../src/logger/Logger.h"

struct TestClientRules : public testing::Test {
    Logger *logger;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<User> users;

    void SetUp() 
    {
        logger = new Logger("log_file.txt", FATAL);
        users.push_back(User(1, "abc", "11111", CLIENT));
        users.push_back(User(2, "abd", "11112", MANAGER));
        users.push_back(User(3, "abe", "11113", CLIENT));
        users.push_back(User(4, "abf", "11114", CLIENT));
        users.push_back(User(5, "abg", "11115", CLIENT));
        managers.push_back(Manager(1, 2, 1));
        clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
        clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
        clients.push_back(Client(3, 4, "a", "a", "a", 77775, 1984, "Street 9", "aa@mail.ru", "+79183456785"));
    }
    void TearDown() 
    { 
        delete logger;
    }
};

TEST_F(TestClientRules, TestGetClientPositive)
{
    //Arrange
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    // Act
    Client tmpClient = crules.getClient(2);

    // Assert
    EXPECT_EQ(tmpClient.getID(), 2);
    EXPECT_EQ(tmpClient.getUserID(), 3);
    EXPECT_EQ(tmpClient.getName(), "b");
    EXPECT_EQ(tmpClient.getSurname(), "b");
    EXPECT_EQ(tmpClient.getPatronymic(), "b");
    EXPECT_EQ(tmpClient.getPassportNum(), 77779);
}

TEST_F(TestClientRules, TestGetClientNegative)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    ASSERT_THROW(crules.getClient(4), ClientNotFoundException);
}

TEST_F(TestClientRules, TestGetClientsByFIO)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    clients = crules.getClientByFIO({.name="a", .surname="a", .patronymic="a"});

    EXPECT_EQ(clients.size(), 2);
    EXPECT_EQ(clients[0].getID(), 1);
    EXPECT_EQ(clients[1].getID(), 3);
    EXPECT_EQ(clients[0].getUserID(), 1);
    EXPECT_EQ(clients[1].getUserID(), 4);
    EXPECT_EQ(clients[0].getName(), "a");
    EXPECT_EQ(clients[0].getSurname(), "a");
    EXPECT_EQ(clients[0].getPatronymic(), "a");
    EXPECT_EQ(clients[1].getName(), "a");
    EXPECT_EQ(clients[1].getSurname(), "a");
    EXPECT_EQ(clients[1].getPatronymic(), "a");
    EXPECT_EQ(clients[0].getPassportNum(), 77777);
    EXPECT_EQ(clients[1].getPassportNum(), 77775);
}

TEST_F(TestClientRules, TestGetAllClients)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    clients = crules.getAllClients();

    EXPECT_EQ(clients.size(), 3);
    EXPECT_EQ(clients[0].getID(), 1);
    EXPECT_EQ(clients[1].getID(), 2);
    EXPECT_EQ(clients[2].getID(), 3);
}


TEST_F(TestClientRules, TestDeleteClientPositive)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    crules.deleteClient(2);

    ASSERT_THROW(crules.getClient(2), ClientNotFoundException);
}

TEST_F(TestClientRules, TestDeleteClientNegative)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    ASSERT_THROW(crules.deleteClient(4), ClientNotFoundException);
}

TEST_F(TestClientRules, TestAddClientPositive)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    int id = crules.addClient({.user_id=5, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
    .email="c@mail.ru", .phone="+79183456783"});

    EXPECT_EQ(crules.getClient(id).getID(), id);
    EXPECT_EQ(crules.getClient(id).getPassportNum(), 99999);
}

TEST_F(TestClientRules, TestAddClientNegativeUserIDBusyByManager)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    ASSERT_THROW(crules.addClient({.user_id=2, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
    .email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST_F(TestClientRules, TestAddClientNegativeUserIDBusyByAnotherClient)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    ASSERT_THROW(crules.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
    .email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST_F(TestClientRules, TestAddClientNegativeEmptySurname)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);

    ASSERT_THROW(crules.addClient({.user_id=4, .name="c", .surname="", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
    .email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST_F(TestClientRules, TestUpdateClientPositive)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);
    Client tmpClient = Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781");
    tmpClient.setEmail("bnew@mail.ru");

    crules.updateClient(tmpClient);

    EXPECT_EQ(crules.getClient(2).getID(), 2);
    EXPECT_EQ(crules.getClient(2).getEmail(), "bnew@mail.ru");
}


TEST_F(TestClientRules, TestUpdateClientNegativeEmptyName)
{
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    MockManagerRepository managerRepository(managers);
    ClientRules crules(clientRepository, userRepository, managerRepository, *logger);
    Client tmpClient = Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781");
    tmpClient.setName("");
    
    ASSERT_THROW(crules.updateClient(tmpClient), ClientUpdateErrorException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}