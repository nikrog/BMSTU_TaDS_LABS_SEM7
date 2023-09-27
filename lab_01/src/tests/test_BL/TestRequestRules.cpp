#include <gtest/gtest.h>
#include "../../business_logic/models/ModelRequest.h"
#include "../../business_logic/rules/RequestRules.h"
#include "../../data_access/MockRepositories/MockRequestRepository.h"
#include "../../data_access/MockRepositories/MockClientRepository.h"
#include "../../data_access/MockRepositories/MockManagerRepository.h"
#include "../../data_access/MockRepositories/MockProductRepository.h"
#include "../../data_access/MockRepositories/MockUserRepository.h"

TEST(TestRequestRules, TestGetRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    Request tmpRequest = rrules.getRequest(2);
    EXPECT_EQ(tmpRequest.getID(), 2);
    EXPECT_EQ(tmpRequest.getClientID(), 2);
    EXPECT_EQ(tmpRequest.getProductID(), 2);
    EXPECT_EQ(tmpRequest.getManagerID(), 1);
    EXPECT_EQ(tmpRequest.getSum(), 100000);
    EXPECT_EQ(tmpRequest.getDuration(), 365);
    EXPECT_EQ(tmpRequest.getDate(), 2023);
    EXPECT_EQ(tmpRequest.getState(), APPROVED);
}

TEST(TestRequestRules, TestGetRequestNegative)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.getRequest(3), RequestNotFoundException);
}

TEST(TestRequestRules, TestGetRequestsByClientPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    requests = rrules.getRequestByClient(1);
    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST(TestRequestRules, TestGetRequestsByClientNegative)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.getRequestByClient(3), RequestGetErrorException);
}

TEST(TestRequestRules, TestGetRequestsByStatePositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    requests = rrules.getRequestByState(APPROVED);
    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 2);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST(TestRequestRules, TestGetRequestsBySumPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 200000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 30000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    requests = rrules.getRequestBySum(20000, 100000);
    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 3);
}


TEST(TestRequestRules, TestGetRequestsBySumNegativeIncorrectSum)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.getRequestBySum(-10000, 900000), RequestGetErrorException);
}

TEST(TestRequestRules, TestGetRequestsBySumNegativeMinSumBiggerThanMaxSum)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.getRequestBySum(100000, 9000), RequestGetErrorException);
}

TEST(TestRequestRules, TestGetRequestsByManager)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 200000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 30000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    requests = rrules.getRequestByManager(1);
    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 2);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST(TestRequestRules, TestGetAllRequests)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 200000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 30000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    requests = rrules.getAllRequests();
    EXPECT_EQ(requests.size(), 3);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 2);
    EXPECT_EQ(requests[2].getID(), 3);
}


TEST(TestRequestRules, TestMakeRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    int id = rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    Request tmpRequest = rrules.getRequest(id);

    EXPECT_EQ(tmpRequest.getID(), id);
    EXPECT_EQ(tmpRequest.getClientID(), 1);
    EXPECT_EQ(tmpRequest.getProductID(), 1);
    EXPECT_EQ(tmpRequest.getManagerID(), NONE);
    EXPECT_EQ(tmpRequest.getSum(), 60000);
    EXPECT_EQ(tmpRequest.getState(), OPENED);
}

TEST(TestRequestRules, TestMakeRequestNegativeClientNotFullAccount)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(5, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeSmallSumForProduct)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=40000, .duration=365, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeBigSumForProduct)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=4000000, .duration=365, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeLongDurationForProduct)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=800, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}


TEST(TestRequestRules, TestMakeRequestNegativeShortDurationForProduct)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=10, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeIncorrectState)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=365, .date=2023, .state=CLOSED}), 
    RequestAddErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeHaveManager)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=1, .sum=900000, .duration=365, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestMakeRequestNegativeNotClient)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    users.push_back(User(5, "abl", "11115", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.makeRequest(1, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=365, .date=2023, .state=OPENED}), 
    RequestMakeErrorException);
}

TEST(TestRequestRules, TestConfirmRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    rrules.confirmRequest(1, 1);
    Request tmpRequest = rrules.getRequest(1);
    EXPECT_EQ(tmpRequest.getState(), APPROVED);
    EXPECT_EQ(tmpRequest.getManagerID(), 1);
}


TEST(TestRequestRules, TestConfirmRequestNegativeNotOpenedRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, CLOSED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.confirmRequest(1, 2), RequestConfirmErrorException);
}

TEST(TestRequestRules, TestConfirmRequestNegativeNonExistentRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, CLOSED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.confirmRequest(4, 2), RequestNotFoundException);
}

TEST(TestRequestRules, TestConfirmRequestNegativeManagerFromAnotherBank)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.confirmRequest(1, 2), RequestConfirmErrorException);
}

TEST(TestRequestRules, TestConfirmRequestNegativeNonExistentManager)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.confirmRequest(1, 3), RequestConfirmErrorException);
}


TEST(TestRequestRules, TestRejectRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    rrules.rejectRequest(1, 1);
    Request tmpRequest = rrules.getRequest(1);
    EXPECT_EQ(tmpRequest.getState(), REJECTED);
    EXPECT_EQ(tmpRequest.getManagerID(), 1);
}


TEST(TestRequestRules, TestRejectRequestNegativeManagerFromAnotherBank)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rejectRequest(1, 2), RequestRejectErrorException);
}

TEST(TestRequestRules, TestRejectRequestNegativeNonExistentManager)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rejectRequest(1, 3), RequestRejectErrorException);
}

TEST(TestRequestRules, TestRejectRequestNegativeNonExistentRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rejectRequest(4, 1), RequestNotFoundException);
}

TEST(TestRequestRules, TestRejectRequestNegativeNotOpenedRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, CLOSED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rejectRequest(1, 2), RequestRejectErrorException);
}


TEST(TestRequestRules, TestUpdateRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    Request tmpRequest = rrules.getRequest(1);
    tmpRequest.setSum(120000);
    rrules.updateRequest(tmpRequest);
    tmpRequest = rrules.getRequest(1);
    EXPECT_EQ(tmpRequest.getID(), 1);
    EXPECT_EQ(tmpRequest.getSum(), 120000);
}

TEST(TestRequestRules, TestUpdateRequestNegativeIncorrectSum)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    Request tmpRequest = rrules.getRequest(1);
    tmpRequest.setSum(-120000);
    ASSERT_THROW(rrules.updateRequest(tmpRequest), RequestUpdateErrorException);
}

TEST(TestRequestRules, TestDeleteRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    rrules.deleteRequest(2);
    ASSERT_THROW(rrules.getRequest(2), RequestNotFoundException);
}

TEST(TestRequestRules, TestDeleteRequestNegative)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.deleteRequest(4), RequestNotFoundException);
}

TEST(TestRequestRules, TestRateRequestPositive)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    rrules.rateProduct(2, 4, 5);
    Request tmpRequest = rrules.getRequest(2);
    EXPECT_EQ(tmpRequest.getState(), APPROVED_SCORED);
}

TEST(TestRequestRules, TestRateRequestNegativeOpenedRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rateProduct(1, 3, 5), ProductRateErrorException);
}

TEST(TestRequestRules, TestRateRequestNegativeAnotherClient)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rateProduct(1, 4, 5), ProductRateErrorException);
}

TEST(TestRequestRules, TestRateRequestNegativeNonExistentRequest)
{
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;
    requests.push_back(Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED));
    requests.push_back(Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED));
    requests.push_back(Request(3, 1, 2, 1, 100000, 365, 2023, APPROVED));
    managers.push_back(Manager(1, 1, 1));
    managers.push_back(Manager(2, 2, 2));
    users.push_back(User(1, "abc", "11111", MANAGER));
    users.push_back(User(2, "abd", "11112", MANAGER));
    users.push_back(User(3, "abe", "11113", CLIENT));
    users.push_back(User(4, "abf", "11114", CLIENT));
    clients.push_back(Client(1, 3, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"));
    clients.push_back(Client(2, 4, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781"));
    products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
    products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository);
    ASSERT_THROW(rrules.rateProduct(4, 4, 5), RequestNotFoundException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}