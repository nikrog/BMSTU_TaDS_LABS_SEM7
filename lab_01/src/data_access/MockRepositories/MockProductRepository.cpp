#include "MockProductRepository.h"

MockProductRepository::~MockProductRepository()
{}

Product MockProductRepository::getProductByID(int id)
{
    for (Product tmpProduct : this->products)
    {
        if (tmpProduct.getID() == id)
            return tmpProduct;
    }
    
    return Product();
}
Product MockProductRepository::getProductByName(std::string name)
{
    for (Product tmpProduct : this->products)
    {
        if (tmpProduct.getName() == name)
            return tmpProduct;
    }
    
    return Product();
}
std::vector<Product> MockProductRepository::getProductByRate(Prodtype type, float rate)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getRate() >= rate))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}
std::vector<Product> MockProductRepository::getProductByBank(Prodtype type, int bank_id)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getBankID() == bank_id))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}

std::vector<Product> MockProductRepository::getProductBySum(Prodtype type, float min_sum, float max_sum)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getMinSum() <= min_sum) && (tmpProduct.getMaxSum() >= max_sum))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}
std::vector<Product> MockProductRepository::getProductByTime(Prodtype type, int min_time, int max_time)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getMinTime() <= min_time) && (tmpProduct.getMaxTime() >= max_time))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}
std::vector<Product> MockProductRepository::getProductByType(Prodtype type)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if (tmpProduct.getType() == type)
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}
std::vector<Product> MockProductRepository::getProductByRating(Prodtype type, float rating)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getAvgRating() >= rating))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}

std::vector<Product> MockProductRepository::getProductByCurrency(Prodtype type, Curtype currency)
{
    std::vector<Product> res_products;
    for (Product tmpProduct : this->products)
    {
        if ((tmpProduct.getType() == type) && (tmpProduct.getCurrency() == currency))
            res_products.push_back(tmpProduct);
    }
    
    return res_products;
}

std::vector<Product> MockProductRepository::getAllProducts()
{
    return this->products;
}
void MockProductRepository::updateEl(Product prod_el)
{
    for (Product tmpProduct : this->products)
    {
        if (tmpProduct.getID() == prod_el.getID())
        {
            this->products[tmpProduct.getID() - 1].setName(prod_el.getName());
            this->products[tmpProduct.getID() - 1].setType(prod_el.getType());
            this->products[tmpProduct.getID() - 1].setRate(prod_el.getRate());
            this->products[tmpProduct.getID() - 1].setMinSum(prod_el.getMinSum());
            this->products[tmpProduct.getID() - 1].setMaxSum(prod_el.getMaxSum());
            this->products[tmpProduct.getID() - 1].setMinTime(prod_el.getMinTime());
            this->products[tmpProduct.getID() - 1].setMaxTime(prod_el.getMaxTime());
            this->products[tmpProduct.getID() - 1].setCurrency(prod_el.getCurrency());
            this->products[tmpProduct.getID() - 1].setCountRating(prod_el.getCountRating());
            this->products[tmpProduct.getID() - 1].setSumRating(prod_el.getSumRating());
        }
    }
    return;
}
void MockProductRepository::deleteEl(int id)
{
    std::vector<Product> new_products;
    for (Product tmpProduct : this->products)
    {
        if (tmpProduct.getID() != id)
            new_products.push_back(tmpProduct);
    }
    this->products = new_products;
}
int MockProductRepository::addProduct(ProductInfo inf)
{
    int N = this->products.size();
    Product tmpProduct = Product(N + 1, inf.bank_id, inf.type, inf.name, inf.rate, inf.min_time, 
    inf.max_time, inf.min_sum, inf.max_sum, inf.currency, inf.sum_rating, inf.count_rating);
    this->products.push_back(tmpProduct);
    return N + 1;
}