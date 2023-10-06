#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgProductRepository.h"
#include "../../src/business_logic/rules/ProductRules.h"
#include "../../src/business_logic/models/ModelProduct.h"
#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"

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
        curConnect.commit();
    }
}

struct TestPgProductRepo : public testing::Test {
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

TEST_F(TestPgProductRepo, TestGetProductByID)
{
    PgProductRepository prep = PgProductRepository(*connectParams);

    Product tmpProduct = prep.getProductByID(2);

    EXPECT_EQ(tmpProduct.getID(), 2);
    EXPECT_EQ(tmpProduct.getBankID(), 2);
    EXPECT_EQ(tmpProduct.getRate(), 12.5);
    EXPECT_EQ(tmpProduct.getName(), "test_credit");
}

TEST_F(TestPgProductRepo, TestGetProductByName)
{
    PgProductRepository prep = PgProductRepository(*connectParams);

    Product tmpProduct = prep.getProductByName("test_credit");

    EXPECT_EQ(tmpProduct.getID(), 2);
    EXPECT_EQ(tmpProduct.getBankID(), 2);
    EXPECT_EQ(tmpProduct.getName(), "test_credit");
}

TEST_F(TestPgProductRepo, TestGetProductByRate)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByRate(DEPOSIT, 14);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 3);
    EXPECT_EQ(products[0].getBankID(), 2);
    EXPECT_EQ(products[0].getName(), "new");
}

TEST_F(TestPgProductRepo, TestGetProductByBank)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByBank(DEPOSIT, 2);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 3);
    EXPECT_EQ(products[0].getBankID(), 2);
    EXPECT_EQ(products[0].getName(), "new");
}

TEST_F(TestPgProductRepo, TestGetProductBySum)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductBySum(DEPOSIT, 10000, 900000);

    EXPECT_EQ(products.size(), 2);
    EXPECT_EQ(products[0].getID(), 1);
    EXPECT_EQ(products[1].getID(), 3);
}

TEST_F(TestPgProductRepo, TestGetProductByTime)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByTime(DEPOSIT, 2, 300);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 3);
}

TEST_F(TestPgProductRepo, TestGetProductByType)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByType(CREDIT);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 2);
}

TEST_F(TestPgProductRepo, TestGetProductByRating)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByRating(DEPOSIT, 4);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 1);
}

TEST_F(TestPgProductRepo, TestGetProductByCurrency)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getProductByCurrency(DEPOSIT, ROUBLE);

    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].getID(), 1);
}

TEST_F(TestPgProductRepo, TestGetAllProducts)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    std::vector<Product> products = std::vector<Product>();

    products = prep.getAllProducts();

    EXPECT_EQ(products.size(), 3);
}

TEST_F(TestPgProductRepo, TestAddProduct)
{
    PgProductRepository prep = PgProductRepository(*connectParams);

    int id = prep.addProduct({.bank_id=1, .type=CREDIT, .name="abc", .rate=10.5, .min_time=100, .max_time=365, .min_sum=1000,
                                .max_sum=700000, .currency=ROUBLE, .sum_rating=10, .count_rating=3});

    Product tmpProduct = prep.getProductByID(id);
    EXPECT_EQ(tmpProduct.getID(), id);
    EXPECT_EQ(tmpProduct.getBankID(), 1);
    EXPECT_EQ(tmpProduct.getName(), "abc");
    EXPECT_EQ(tmpProduct.getRate(), 10.5);
}

TEST_F(TestPgProductRepo, TestUpdateProduct)
{
    PgProductRepository prep = PgProductRepository(*connectParams);
    Product tmpProduct = Product(3, 2, DEPOSIT, "new", 15, 1, 365, 10000,
    1000000, DOLLAR, 0, 0);
    tmpProduct.setRate(8.5);

    prep.updateEl(tmpProduct);

    EXPECT_EQ(prep.getProductByID(3).getRate(), 8.5);
}

TEST_F(TestPgProductRepo, TestDeleteProduct)
{
    PgProductRepository prep = PgProductRepository(*connectParams);

    prep.deleteEl(3);

    EXPECT_EQ(prep.getAllProducts().size(), 2);  
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
