#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgRequestRepository.h"
#include "../../src/business_logic/rules/RequestRules.h"
#include "../../src/business_logic/models/ModelRequest.h"
#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/data_access/PostgresRepositories/PgProductRepository.h"
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"

struct TestPgRequestRepo : public testing::Test {
    ConnectionParams *connectParams;

    void SetUp() 
    {
        connectParams = new ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    }
    void TearDown() 
    { 
        delete connectParams;
    }
};

TEST_F(TestPgRequestRepo, TestGetRequestByID)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    Request request = rrep.getRequestByID(1);

    EXPECT_EQ(request.getID(), 1);
    EXPECT_EQ(request.getClientID(), 1);
    EXPECT_EQ(request.getProductID(), 1);
    EXPECT_EQ(request.getManagerID(), 1);
    EXPECT_EQ(request.getState(), APPROVED);
}

TEST_F(TestPgRequestRepo, TestGetRequestByState)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getRequestByState(APPROVED);

    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[0].getClientID(), 1);
    EXPECT_EQ(requests[0].getProductID(), 1);
    EXPECT_EQ(requests[0].getState(), APPROVED);
}

TEST_F(TestPgRequestRepo, TestGetRequestByClient)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getRequestByClient(1);

    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[0].getClientID(), 1);
}

TEST_F(TestPgRequestRepo, TestGetRequestBySum)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getRequestBySum(60000, 80000);

    EXPECT_EQ(requests.size(), 1);
}

TEST_F(TestPgRequestRepo, TestGetRequestByManager)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getRequestByManager(1);

    EXPECT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0].getID(), 1);
    EXPECT_EQ(requests[1].getID(), 2);
}

TEST_F(TestPgRequestRepo, TestGetRequestByDate)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getRequestByDate("2023-10-04");

    EXPECT_EQ(requests.size(), 1);
    EXPECT_EQ(requests[0].getID(), 1);
}

TEST_F(TestPgRequestRepo, TestRequestByDuration)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();
    
    requests = rrep.getRequestByDuration(300, 399);

    EXPECT_EQ(requests.size(), 1);
}

TEST_F(TestPgRequestRepo, TestGetAllRequests)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    std::vector<Request> requests = std::vector<Request>();

    requests = rrep.getAllRequests();

    EXPECT_EQ(requests.size(), 2);
}


TEST_F(TestPgRequestRepo, TestUpdateRequest)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);
    Request tmpRequest = Request(1, 1, 1, 1, 60000, 365, "2023-10-04", APPROVED);
    tmpRequest.setSum(70000);

    rrep.updateEl(tmpRequest);

    tmpRequest = rrep.getRequestByID(1);
    EXPECT_EQ(tmpRequest.getID(), 1);
    EXPECT_EQ(tmpRequest.getSum(), 70000);
}

TEST_F(TestPgRequestRepo, TestAddRequest)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);

    int id = rrep.addRequest({.client_id=1, .product_id=1, .manager_id=NONE, .sum=800000, .duration=180, .date="2023-10-04", .state=OPENED});

    Request tmpRequest = rrep.getRequestByID(id);
    EXPECT_EQ(tmpRequest.getID(), id);
    EXPECT_EQ(tmpRequest.getClientID(), 1);
    EXPECT_EQ(tmpRequest.getProductID(), 1);
}

TEST_F(TestPgRequestRepo, TestDeleteRequest)
{
    PgRequestRepository rrep = PgRequestRepository(*connectParams);

    rrep.deleteEl(3);

    std::vector<Request> requests = rrep.getAllRequests();
    EXPECT_EQ(requests.size(), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

