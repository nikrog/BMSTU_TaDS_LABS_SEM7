#include <gtest/gtest.h>
#include "../../business_logic/models/ModelClient.h"
#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/models/ModelManager.h"
#include "../../business_logic/rules/ClientRules.h"
#include "../../data_access/MockRepositories/MockClientRepository.h"
#include "../../data_access/MockRepositories/MockUserRepository.h"
#include "../../data_access/MockRepositories/MockManagerRepository.h"

 
TEST(TestClientRules, TestGetClientPositive)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
Client tmpClient = crules.getClient(2);
EXPECT_EQ(tmpClient.getID(), 2);
EXPECT_EQ(tmpClient.getUserID(), 3);
EXPECT_EQ(tmpClient.getName(), "b");
EXPECT_EQ(tmpClient.getSurname(), "b");
EXPECT_EQ(tmpClient.getPatronymic(), "b");
EXPECT_EQ(tmpClient.getPassportNum(), 77779);
}

TEST(TestClientRules, TestGetClientNegative)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
ASSERT_THROW(crules.getClient(3), ClientNotFoundException);
}

TEST(TestClientRules, TestGetClientsByFIO)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "b", "b", "b", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
clients.push_back(Client(2, 4, "a", "a", "a", 77775, 1984, "Street 9", "aa@mail.ru", "+79183456785"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
clients = crules.getClientByFIO({.name="b", .surname="b", .patronymic="b"});
EXPECT_EQ(clients.size(), 2);
EXPECT_EQ(clients[0].getID(), 1);
EXPECT_EQ(clients[1].getID(), 2);
EXPECT_EQ(clients[0].getUserID(), 1);
EXPECT_EQ(clients[1].getUserID(), 3);
EXPECT_EQ(clients[0].getName(), "b");
EXPECT_EQ(clients[0].getSurname(), "b");
EXPECT_EQ(clients[0].getPatronymic(), "b");
EXPECT_EQ(clients[1].getName(), "b");
EXPECT_EQ(clients[1].getSurname(), "b");
EXPECT_EQ(clients[1].getPatronymic(), "b");
EXPECT_EQ(clients[0].getPassportNum(), 77777);
EXPECT_EQ(clients[1].getPassportNum(), 77779);
}

TEST(TestClientRules, TestGetAllClients)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
clients = crules.getAllClients();
EXPECT_EQ(clients.size(), 2);
EXPECT_EQ(clients[0].getID(), 1);
EXPECT_EQ(clients[1].getID(), 2);
}


TEST(TestClientRules, TestDeleteClientPositive)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
crules.deleteClient(2);
ASSERT_THROW(crules.getClient(2), ClientNotFoundException);
}

TEST(TestClientRules, TestDeleteClientNegative)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
ASSERT_THROW(crules.deleteClient(3), ClientNotFoundException);
}

TEST(TestClientRules, TestAddClientPositive)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
int id = crules.addClient({.user_id=4, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
.email="c@mail.ru", .phone="+79183456783"});
Client tmpClient = crules.getClient(id);
EXPECT_EQ(tmpClient.getID(), id);
EXPECT_EQ(tmpClient.getPassportNum(), 99999);
}

TEST(TestClientRules, TestAddClientNegativeUserIDBusyByManager)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
ASSERT_THROW(crules.addClient({.user_id=2, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
.email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST(TestClientRules, TestAddClientNegativeUserIDBusyByAnotherClient)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
ASSERT_THROW(crules.addClient({.user_id=3, .name="c", .surname="c", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
.email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST(TestClientRules, TestAddClientNegativeEmptySurname)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
ASSERT_THROW(crules.addClient({.user_id=4, .name="c", .surname="", .patronymic="c", .passport_num=99999, .birth_date=1977, .address="Street 11",
.email="c@mail.ru", .phone="+79183456783"}), ClientAddErrorException);
}

TEST(TestClientRules, TestUpdateClientPositive)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
Client tmpClient = crules.getClient(2);
tmpClient.setEmail("bnew@mail.ru");
crules.updateClient(tmpClient);
tmpClient = crules.getClient(2);
EXPECT_EQ(tmpClient.getID(), 2);
EXPECT_EQ(tmpClient.getEmail(), "bnew@mail.ru");
}


TEST(TestClientRules, TestUpdateClientNegativeEmptyName)
{
std::vector<Client> clients;
std::vector<User> users;
std::vector<Manager> managers;
users.push_back(User(1, "abc", "11111", CLIENT));
users.push_back(User(2, "abd", "11112", MANAGER));
users.push_back(User(3, "abe", "11113", CLIENT));
users.push_back(User(4, "abf", "11114", CLIENT));
managers.push_back(Manager(1, 2, 1));
clients.push_back(Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
clients.push_back(Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
MockClientRepository clientRepository(clients);
MockUserRepository userRepository(users);
MockManagerRepository managerRepository(managers);
ClientRules crules(clientRepository, userRepository, managerRepository);
Client tmpClient = crules.getClient(2);
tmpClient.setName("");
ASSERT_THROW(crules.updateClient(tmpClient), ClientUpdateErrorException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}