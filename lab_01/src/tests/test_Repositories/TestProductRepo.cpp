#include <gtest/gtest.h>

#include "../../data_access/PostgresRepositories/PgProductRepository.h"
#include "../../business_logic/rules/ProductRules.h"
#include "../../business_logic/models/ModelProduct.h"
#include "../../data_access/PostgresRepositories/PgBankRepository.h"

TEST(TestPgProductRepo, TestGetProductByName)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgBankRepository brep = PgBankRepository(connectParams);
    
    ProductRules prules(prep, brep);

    Product tmpProduct = prules.getProductByName("test_credit");
    EXPECT_EQ(tmpProduct.getID(), 2);
    EXPECT_EQ(tmpProduct.getBankID(), 1);
    EXPECT_EQ(tmpProduct.getName(), "test_credit");
}

TEST(TestPgProductRepo, TestUpdateProduct)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgBankRepository brep = PgBankRepository(connectParams);
    
    ProductRules prules(prep, brep);

    int id = prules.addProduct({.bank_id=1, .type=CREDIT, .name="abc", .rate=10.5, .min_time=100, .max_time=365, .min_sum=1000,
                                .max_sum=700000, .currency=ROUBLE, .sum_rating=10, .count_rating=3});
    Product tmpProduct = prules.getProduct(id);
    EXPECT_EQ(tmpProduct.getID(), id);
    EXPECT_EQ(tmpProduct.getBankID(), 1);
    EXPECT_EQ(tmpProduct.getName(), "abc");
    EXPECT_EQ(tmpProduct.getRate(), 10.5);

    tmpProduct.setRate(8.5);
    prules.updateProduct(tmpProduct);
    tmpProduct = prules.getProduct(id);
    EXPECT_EQ(tmpProduct.getRate(), 8.5);

    prules.deleteProduct(id);
    ASSERT_THROW(prules.getProduct(id), ProductNotFoundException);
}

TEST(TestPgProductRepo, TestAddandDeleteProduct)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgBankRepository brep = PgBankRepository(connectParams);
    
    ProductRules prules(prep, brep);

    int id = prules.addProduct({.bank_id=1, .type=CREDIT, .name="abc", .rate=10.5, .min_time=100, .max_time=365, .min_sum=1000,
                                .max_sum=700000, .currency=ROUBLE, .sum_rating=10, .count_rating=3});
    Product tmpProduct = prules.getProduct(id);
    EXPECT_EQ(tmpProduct.getID(), id);
    EXPECT_EQ(tmpProduct.getBankID(), 1);
    EXPECT_EQ(tmpProduct.getName(), "abc");
    prules.deleteProduct(id);
    ASSERT_THROW(prules.getProduct(id), ProductNotFoundException);
}

TEST(TestPgProductRepo, TestGetAllProducts)
{
    ConnectionParams connectParams = ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
    PgProductRepository prep = PgProductRepository(connectParams);
    PgBankRepository brep = PgBankRepository(connectParams);
    
    ProductRules prules(prep, brep);

    std::vector<Product> products = std::vector<Product>();
    products = prules.getAllProducts();
    EXPECT_EQ(products.size(), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
