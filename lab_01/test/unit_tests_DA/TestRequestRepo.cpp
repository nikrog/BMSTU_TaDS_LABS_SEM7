#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgRequestRepository.h"
#include "../../src/business_logic/rules/RequestRules.h"
#include "../../src/business_logic/models/ModelRequest.h"
#include "../../src/data_access/PostgresRepositories/PgClientRepository.h"
#include "../../src/data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../src/data_access/PostgresRepositories/PgProductRepository.h"
#include "../../src/data_access/PostgresRepositories/PgUserRepository.h"

void load_data(ConnectionParams params)
{   
    std::string connect_str = params.getString();
    std::shared_ptr<pqxx::connection> connection = std::make_shared<pqxx::connection>(connect_str.c_str());

    if (connection->is_open())
    {
        //std::string sql = PostgreSQLGetUserID().get_str(login);
        pqxx::work curConnect(*connection);
        curConnect.exec("TRUNCATE TABLE BA.requests RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.products RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.clients RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.managers RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.banks RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.users RESTART IDENTITY CASCADE;");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('admin', 'admin', 3);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('manager', '11111', 2);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('client', '22221', 1);");
        curConnect.exec("INSERT INTO BA.users (login, password, permission) VALUES ('client2', '22222', 1);");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Альфа банк', 1234, 'Москва', 'alphabank@alpha.ru', '+74953459872', 'alphabank.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Райфайзен банк', 1235, 'Москва', 'raifaizen@raif.ru', '+74953459873', 'raiffaizen.ru');");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Россельхоз банк', 6667, 'Москва', 'rosselhoz@rsb.ru', '+74953479973', 'rosselhoz.ru');");
        curConnect.exec("INSERT INTO BA.managers (user_id, bank_id) VALUES (2, 1)");
        curConnect.exec("INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES " \
        "('b', 'b', 'b', 7777912345, 19860203, 'Street 9', 'b@mail.ru', '+79183456781', 4);");
        curConnect.exec("INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES " \
        "('a', 'a', 'a', 7776933333, 19990623, 'Street 6', 'a@mail.ru', '+79183456745', 3);");
        curConnect.exec("INSERT INTO BA.products (ptype, name, bank_id, rate, min_time, max_time, " \
        "min_sum, max_sum, currency, sum_rating, count_rating)  VALUES " \
        "(0, 'test', 1, 7.5, 10, 750, 10000, 1000000, 0, 5, 1);");
        curConnect.exec("INSERT INTO BA.products (ptype, name, bank_id, rate, min_time, max_time, " \
        "min_sum, max_sum, currency, sum_rating, count_rating)  VALUES " \
        "(1, 'test_credit', 2, 12.5, 1, 750, 100000, 3000000, 0, 21, 5);");
        curConnect.exec("INSERT INTO BA.products (ptype, name, bank_id, rate, min_time, max_time, " \
        "min_sum, max_sum, currency, sum_rating, count_rating)  VALUES " \
        "(0, 'new', 2, 15, 1, 365, 10000, 1000000, 1, 0, 0);");
        curConnect.exec("INSERT INTO BA.requests (client_id, product_id, manager_id, sum, duration, date, state) VALUES " \
        "(1, 1, 1, 60000, 365, '2023-10-04', 1);");
        curConnect.exec("INSERT INTO BA.requests (client_id, product_id, manager_id, sum, duration, date, state) VALUES " \
        "(2, 1, 1, 90000, 400, '2023-09-04', 2);");
        curConnect.commit();
    }
}

struct TestPgRequestRepo : public testing::Test {
    ConnectionParams *connectParams;

    void SetUp() 
    {
        connectParams = new ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
        load_data(*connectParams);
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

    rrep.deleteEl(2);

    std::vector<Request> requests = rrep.getAllRequests();
    EXPECT_EQ(requests.size(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

