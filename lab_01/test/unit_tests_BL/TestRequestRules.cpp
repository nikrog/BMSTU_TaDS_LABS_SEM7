#include <gtest/gtest.h>
#include "../../src/business_logic/models/ModelRequest.h"
#include "../../src/business_logic/rules/RequestRules.h"
#include "../../src/data_access/MockRepositories/MockRequestRepository.h"
#include "../../src/data_access/MockRepositories/MockClientRepository.h"
#include "../../src/data_access/MockRepositories/MockManagerRepository.h"
#include "../../src/data_access/MockRepositories/MockProductRepository.h"
#include "../../src/data_access/MockRepositories/MockUserRepository.h"
#include "../../src/logger/Logger.h"

struct TestRequestRules : public testing::Test {
    Logger *logger;
    std::vector<Request> requests;
    std::vector<Manager> managers;
    std::vector<Client> clients;
    std::vector<Product> products;
    std::vector<User> users;

    void SetUp() 
    {
        logger = new Logger("log_file.txt", FATAL);
        requests.push_back(Request(1, 1, 1, NONE, 100000, 365, "2023", OPENED));
        requests.push_back(Request(2, 2, 2, 1, 100000, 365, "2023", APPROVED));
        requests.push_back(Request(3, 1, 2, 1, 30000, 365, "2023", APPROVED));
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
    }
    void TearDown() 
    { 
        delete logger;
    }
};

TEST_F(TestRequestRules, TestGetRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    Request tmpRequest = rrules.getRequest(2);

    EXPECT_EQ(tmpRequest.getID(), 2);
    EXPECT_EQ(tmpRequest.getClientID(), 2);
    EXPECT_EQ(tmpRequest.getProductID(), 2);
    EXPECT_EQ(tmpRequest.getManagerID(), 1);
    EXPECT_EQ(tmpRequest.getSum(), 100000);
    EXPECT_EQ(tmpRequest.getDuration(), 365);
    EXPECT_EQ(tmpRequest.getDate(), "2023");
    EXPECT_EQ(tmpRequest.getState(), APPROVED);
}

TEST_F(TestRequestRules, TestGetRequestNegative)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.getRequest(4), RequestNotFoundException);
}

TEST_F(TestRequestRules, TestGetRequestsByClientPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    requests = rrules.getRequestByClient(1);

    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST_F(TestRequestRules, TestGetRequestsByClientNegative)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.getRequestByClient(3), RequestGetErrorException);
}

TEST_F(TestRequestRules, TestGetRequestsByStatePositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    requests = rrules.getRequestByState(APPROVED);

    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 2);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST_F(TestRequestRules, TestGetRequestsBySumPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    requests = rrules.getRequestBySum(40000, 100000);

    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 2);
}


TEST_F(TestRequestRules, TestGetRequestsBySumNegativeIncorrectSum)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.getRequestBySum(-10000, 900000), RequestGetErrorException);
}

TEST_F(TestRequestRules, TestGetRequestsBySumNegativeMinSumBiggerThanMaxSum)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.getRequestBySum(100000, 9000), RequestGetErrorException);
}

TEST_F(TestRequestRules, TestGetRequestsByManager)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    requests = rrules.getRequestByManager(1);

    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 2);
    EXPECT_EQ(requests[1].getID(), 3);
}

TEST_F(TestRequestRules, TestGetAllRequests)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    requests = rrules.getAllRequests();

    EXPECT_EQ(requests.size(), 3);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 2);
    EXPECT_EQ(requests[2].getID(), 3);
}


TEST_F(TestRequestRules, TestMakeRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    int id = rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date="2023", .state=OPENED});

    EXPECT_EQ(rrules.getRequest(id).getID(), id);
    EXPECT_EQ(rrules.getRequest(id).getClientID(), 1);
    EXPECT_EQ(rrules.getRequest(id).getProductID(), 1);
    EXPECT_EQ(rrules.getRequest(id).getManagerID(), NONE);
    EXPECT_EQ(rrules.getRequest(id).getSum(), 60000);
    EXPECT_EQ(rrules.getRequest(id).getState(), OPENED);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeClientNotFullAccount)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(5, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeSmallSumForProduct)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=40000, .duration=365, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeBigSumForProduct)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=4000000, .duration=365, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeLongDurationForProduct)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=800, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}


TEST_F(TestRequestRules, TestMakeRequestNegativeShortDurationForProduct)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=10, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeIncorrectState)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=365, .date="2023", .state=CLOSED}), 
    RequestAddErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeHaveManager)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(3, {.client_id=1, .product_id=1, .manager_id=1, .sum=900000, .duration=365, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestMakeRequestNegativeNotClient)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.makeRequest(1, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=900000, .duration=365, .date="2023", .state=OPENED}), 
    RequestMakeErrorException);
}

TEST_F(TestRequestRules, TestConfirmRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    rrules.confirmRequest(1, 1);

    EXPECT_EQ(rrules.getRequest(1).getState(), APPROVED);
    EXPECT_EQ(rrules.getRequest(1).getManagerID(), 1);
}


TEST_F(TestRequestRules, TestConfirmRequestNegativeNotOpenedRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.confirmRequest(1, 2), RequestConfirmErrorException);
}

TEST_F(TestRequestRules, TestConfirmRequestNegativeNonExistentRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.confirmRequest(4, 2), RequestNotFoundException);
}

TEST_F(TestRequestRules, TestConfirmRequestNegativeManagerFromAnotherBank)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.confirmRequest(1, 2), RequestConfirmErrorException);
}

TEST_F(TestRequestRules, TestConfirmRequestNegativeNonExistentManager)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.confirmRequest(1, 3), RequestConfirmErrorException);
}


TEST_F(TestRequestRules, TestRejectRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    rrules.rejectRequest(1, 1);

    Request tmpRequest = rrules.getRequest(1);
    EXPECT_EQ(rrules.getRequest(1).getState(), REJECTED);
    EXPECT_EQ(rrules.getRequest(1).getManagerID(), 1);
}


TEST_F(TestRequestRules, TestRejectRequestNegativeManagerFromAnotherBank)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rejectRequest(1, 2), RequestRejectErrorException);
}

TEST_F(TestRequestRules, TestRejectRequestNegativeNonExistentManager)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rejectRequest(1, 3), RequestRejectErrorException);
}

TEST_F(TestRequestRules, TestRejectRequestNegativeNonExistentRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rejectRequest(4, 1), RequestNotFoundException);
}

TEST_F(TestRequestRules, TestRejectRequestNegativeNotOpenedRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rejectRequest(1, 2), RequestRejectErrorException);
}


TEST_F(TestRequestRules, TestUpdateRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);
    Request tmpRequest = Request(1, 1, 1, NONE, 100000, 365, "2023", OPENED);
    tmpRequest.setSum(120000);

    rrules.updateRequest(tmpRequest);

    EXPECT_EQ(rrules.getRequest(1).getID(), 1);
    EXPECT_EQ(rrules.getRequest(1).getSum(), 120000);
}

TEST_F(TestRequestRules, TestUpdateRequestNegativeIncorrectSum)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);
    Request tmpRequest = Request(1, 1, 1, NONE, 100000, 365, "2023", OPENED);
    tmpRequest.setSum(-120000);

    ASSERT_THROW(rrules.updateRequest(tmpRequest), RequestUpdateErrorException);
}

TEST_F(TestRequestRules, TestDeleteRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    rrules.deleteRequest(2);

    ASSERT_THROW(rrules.getRequest(2), RequestNotFoundException);
}

TEST_F(TestRequestRules, TestDeleteRequestNegative)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.deleteRequest(4), RequestNotFoundException);
}

TEST_F(TestRequestRules, TestRateRequestPositive)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    rrules.rateProduct(2, 4, 5);

    EXPECT_EQ(rrules.getRequest(2).getState(), APPROVED_SCORED);
}

TEST_F(TestRequestRules, TestRateRequestNegativeOpenedRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rateProduct(1, 3, 5), ProductRateErrorException);
}

TEST_F(TestRequestRules, TestRateRequestNegativeAnotherClient)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rateProduct(1, 4, 5), ProductRateErrorException);
}

TEST_F(TestRequestRules, TestRateRequestNegativeNonExistentRequest)
{
    MockRequestRepository requestRepository(requests);
    MockManagerRepository managerRepository(managers);
    MockProductRepository productRepository(products);
    MockClientRepository clientRepository(clients);
    MockUserRepository userRepository(users);
    RequestRules rrules(requestRepository, clientRepository, managerRepository, productRepository, userRepository, *logger);

    ASSERT_THROW(rrules.rateProduct(4, 4, 5), RequestNotFoundException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}