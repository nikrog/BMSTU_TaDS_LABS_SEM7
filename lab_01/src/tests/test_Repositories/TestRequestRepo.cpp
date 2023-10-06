#include <gtest/gtest.h>

#include "../../data_access/PostgresRepositories/PgRequestRepository.h"
#include "../../business_logic/rules/RequestRules.h"
#include "../../business_logic/models/ModelRequest.h"
#include "../../data_access/PostgresRepositories/PgClientRepository.h"
#include "../../data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../data_access/PostgresRepositories/PgProductRepository.h"
#include "../../data_access/PostgresRepositories/PgUserRepository.h"

TEST(TestPgRequestRepo, TestGetRequestByState)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);
    std::vector<Request> requests = std::vector<Request>();

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    requests = rrules.getRequestByState(OPENED);
    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), id);
    EXPECT_EQ(requests[0].getClientID(), 1);
    EXPECT_EQ(requests[0].getProductID(), 1);
    EXPECT_EQ(requests[0].getState(), OPENED);
    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestGetRequestByClient)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);
    std::vector<Request> requests = std::vector<Request>();

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    requests = rrules.getRequestByClient(1);
    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), id);
    EXPECT_EQ(requests[0].getClientID(), 1);
    EXPECT_EQ(requests[0].getProductID(), 1);
    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestGetRequestBySum)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);
    std::vector<Request> requests = std::vector<Request>();

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    requests = rrules.getRequestBySum(10000, 100000);
    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), id);
    EXPECT_EQ(requests[0].getClientID(), 1);
    EXPECT_EQ(requests[0].getProductID(), 1);

    requests = rrules.getRequestBySum(60000, 100000);
    EXPECT_EQ(requests.size(), 1);

    requests = rrules.getRequestBySum(50000, 60000);
    EXPECT_EQ(requests.size(), 1);

    requests = rrules.getRequestBySum(50000, 59000);
    EXPECT_EQ(requests.size(), 0);

    requests = rrules.getRequestBySum(61000, 100000);
    EXPECT_EQ(requests.size(), 0);

    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestGetRequestByManager)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);
    std::vector<Request> requests = std::vector<Request>();

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    requests = rrules.getRequestByManager(NONE);
    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), id);
    EXPECT_EQ(requests[0].getClientID(), 1);
    EXPECT_EQ(requests[0].getProductID(), 1);
    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestUpdateRequest)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    Request tmpRequest = rrules.getRequest(id);
    EXPECT_EQ(tmpRequest.getID(), id);
    EXPECT_EQ(tmpRequest.getClientID(), 1);
    EXPECT_EQ(tmpRequest.getProductID(), 1);
    EXPECT_EQ(tmpRequest.getSum(), 60000);

    tmpRequest.setSum(120000);
    rrules.updateRequest(tmpRequest);
    tmpRequest = rrules.getRequest(id);
    EXPECT_EQ(tmpRequest.getID(), id);
    EXPECT_EQ(tmpRequest.getSum(), 120000);
    
    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestAddandDeleteRequest)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});
    Request tmpRequest = rrules.getRequest(id);
    EXPECT_EQ(tmpRequest.getID(), id);
    EXPECT_EQ(tmpRequest.getClientID(), 1);
    EXPECT_EQ(tmpRequest.getProductID(), 1);
    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);
}

TEST(TestPgRequestRepo, TestGetAllRequests)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgRequestRepository rrep = PgRequestRepository(connectParams);
    PgManagerRepository mrep = PgManagerRepository(connectParams);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgClientRepository crep = PgClientRepository(connectParams);
    PgUserRepository urep = PgUserRepository(connectParams);
    
    RequestRules rrules(rrep, crep, mrep, prep, urep);

    int id = rrules.makeRequest(4, {.client_id=1, .product_id=1, .manager_id=NONE, .sum=60000, .duration=365, .date=2023, .state=OPENED});

    std::vector<Request> requests = std::vector<Request>();
    requests = rrules.getAllRequests();
    EXPECT_EQ(requests.size(), 1);

    rrules.deleteRequest(id);
    ASSERT_THROW(rrules.getRequest(id), RequestNotFoundException);

    requests = rrules.getAllRequests();
    EXPECT_EQ(requests.size(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

