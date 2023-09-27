#include <gtest/gtest.h>
#include "../../business_logic/models/ModelProduct.h"
#include "../../business_logic/rules/ProductRules.h"
#include "../../data_access/MockRepositories/MockProductRepository.h"
#include "../../data_access/MockRepositories/MockBankRepository.h"


TEST(TestProductRules, TestGetProductPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
Product tmpProduct = prules.getProduct(2);
EXPECT_EQ(tmpProduct.getID(), 2);
EXPECT_EQ(tmpProduct.getName(), "second");
EXPECT_EQ(tmpProduct.getRate(), 7.5);
EXPECT_EQ(tmpProduct.getMinTime(), 180);
EXPECT_EQ(tmpProduct.getMaxTime(), 750);
EXPECT_EQ(tmpProduct.getMinSum(), 50000);
EXPECT_EQ(tmpProduct.getMaxSum(), 1000000);
EXPECT_EQ(tmpProduct.getCurrency(), DOLLAR);
EXPECT_EQ(tmpProduct.getAvgRating(), 0);
}

TEST(TestProductRules, TestGetProductNegative)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProduct(3), ProductNotFoundException);
}

TEST(TestProductRules, TestGetProductByNamePositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
Product tmpProduct = prules.getProductByName("second");
EXPECT_EQ(tmpProduct.getID(), 2);
EXPECT_EQ(tmpProduct.getName(), "second");
EXPECT_EQ(tmpProduct.getRate(), 7.5);
EXPECT_EQ(tmpProduct.getMinTime(), 180);
EXPECT_EQ(tmpProduct.getMaxTime(), 750);
EXPECT_EQ(tmpProduct.getMinSum(), 50000);
EXPECT_EQ(tmpProduct.getMaxSum(), 1000000);
EXPECT_EQ(tmpProduct.getCurrency(), DOLLAR);
EXPECT_EQ(tmpProduct.getAvgRating(), 0);
}

TEST(TestProductRules, TestGetProductByNameNegative)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProductByName("third"), ProductNotFoundException);
}

TEST(TestProductRules, TestGetAllProducts)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0));
products.push_back(Product(2, 1, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
products = prules.getAllProducts();
EXPECT_EQ(products.size(), 2);
EXPECT_EQ(products[0].getName(), "first");
EXPECT_EQ(products[1].getName(), "second");
}

TEST(TestProductRules, TestGetProductByRatingPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
products = prules.getProductByRating(DEPOSIT, 4.5);
EXPECT_EQ(products.size(), 2);
EXPECT_EQ(products[0].getName(), "second");
EXPECT_EQ(products[1].getName(), "third");
}

TEST(TestProductRules, TestGetProductByRatingNegative)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProductByRating(DEPOSIT, -1.0), ProductGetErrorException);
}

TEST(TestProductRules, TestGetProductByBankPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 2, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 2, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 2, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
products = prules.getProductByBank(DEPOSIT, 2);
EXPECT_EQ(products.size(), 2);
EXPECT_EQ(products[0].getName(), "first");
EXPECT_EQ(products[1].getName(), "third");
}

TEST(TestProductRules, TestGetProductByBankNegativeNonExistentBank)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProductByBank(DEPOSIT, 3), ProductGetErrorException);
}

TEST(TestProductRules, TestGetProductBySumPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 2, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 2, DEPOSIT, "third", 7.5, 180, 750,  5000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 2, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
products = prules.getProductBySum(DEPOSIT, 10000, 500000);
EXPECT_EQ(products.size(), 1);
EXPECT_EQ(products[0].getName(), "third");
}

TEST(TestProductRules, TestGetProductBySumNegativeIncorrectSumNegative)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProductBySum(DEPOSIT, -10000, 500000), ProductGetErrorException);
}

TEST(TestProductRules, TestGetProductBySumNegativeMinSumBiggerThanMaxSum)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.getProductBySum(DEPOSIT, 1000000, 500000), ProductGetErrorException);
}

TEST(TestProductRules, TestDeleteProductPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
prules.deleteProduct(3);
ASSERT_THROW(prules.getProduct(3), ProductNotFoundException);
}

TEST(TestProductRules, TestDeleteProductNegative)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.deleteProduct(5), ProductNotFoundException);
}

TEST(TestProductRules, TestAddProductPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
int id = prules.addProduct({.bank_id=2, .type=CREDIT, .name="abc", .rate=10.5, .min_time=100, .max_time=365, .min_sum=1000,
 .max_sum=700000, .currency=ROUBLE, .sum_rating=10, .count_rating=3});
Product tmpProduct = prules.getProduct(id);
EXPECT_EQ(tmpProduct.getID(), id);
EXPECT_EQ(tmpProduct.getName(), "abc");
EXPECT_EQ(tmpProduct.getBankID(), 2);
}

TEST(TestProductRules, TestAddProductNegativeEmptyName)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
ASSERT_THROW(prules.addProduct({.bank_id=2, .type=CREDIT, .name="", .rate=10.5, .min_time=100, .max_time=365, .min_sum=1000,
 .max_sum=700000, .currency=ROUBLE, .sum_rating=10, .count_rating=3}), ProductAddErrorException);
}

TEST(TestProductRules, TestUpdateProductPositive)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
Product tmpProduct = prules.getProduct(2);
tmpProduct.setRate(8.5);
prules.updateProduct(tmpProduct);
tmpProduct = prules.getProduct(2);
EXPECT_EQ(tmpProduct.getRate(), 8.5);
}

TEST(TestProductRules, TestUpdateProductNegativeIncorrectRate)
{
std::vector<Bank> banks;
std::vector<Product> products;
banks.push_back(Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"));
banks.push_back(Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru"));
products.push_back(Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 3, 1));
products.push_back(Product(2, 1, DEPOSIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 10, 2));
products.push_back(Product(3, 1, DEPOSIT, "third", 7.5, 180, 750,  50000, 1000000, DOLLAR, 14, 3));
products.push_back(Product(4, 1, CREDIT, "dddd", 7.5, 180, 750,  50000, 1000000, DOLLAR, 15, 3));
MockBankRepository bankRepository(banks);
MockProductRepository productRepository(products);
ProductRules prules(productRepository, bankRepository);
Product tmpProduct = prules.getProduct(2);
tmpProduct.setMinTime(-1);
ASSERT_THROW(prules.updateProduct(tmpProduct), ProductUpdateErrorException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
