#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgProductRepository.h"
#include "../../src/business_logic/rules/ProductRules.h"
#include "../../src/business_logic/models/ModelProduct.h"
#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"

struct TestPgProductRepo : public testing::Test {
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
    Product tmpProduct = Product(4, 1, CREDIT, "abc", 10.5, 100, 365, 1000,
    700000, ROUBLE, 10, 3);
    tmpProduct.setRate(8.5);

    prep.updateEl(tmpProduct);

    EXPECT_EQ(prep.getProductByID(4).getRate(), 8.5);
}

TEST_F(TestPgProductRepo, TestDeleteProduct)
{
    PgProductRepository prep = PgProductRepository(*connectParams);

    prep.deleteEl(4);

    EXPECT_EQ(prep.getAllProducts().size(), 3);  
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
