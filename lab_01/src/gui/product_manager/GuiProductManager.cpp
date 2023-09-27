#include "GuiProductManager.h"

GUIProductManager::GUIProductManager(ProductRules &pController)
{
    this->productController = pController;
}

GUIProductManager::GUIProductManager(){}

std::vector<Product> GUIProductManager::viewAllProducts()
{
    std::vector<Product> products = this->productController.getAllProducts();
    return products;
}

std::vector<Product> GUIProductManager::viewProductsByType(Prodtype t)
{
    std::vector<Product> products = this->productController.getProductByType(t);
    return products;
}

std::vector<Product> GUIProductManager::viewFilterProducts(ProductFilter f)
{
    std::vector<Product> products = this->productController.filterProducts(f);
    return products;
}

Product GUIProductManager::viewProduct(int id)
{
    Product p = this->productController.getProduct(id);
    return p;
}

void GUIProductManager::addProduct(ProductInfo inf)
{
    int id = this->productController.addProduct(inf);
    Product tmpProd = this->productController.getProduct(id);
    if (tmpProd.getID() == NONE)
    {
        throw ProductAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

void GUIProductManager::deleteProduct(int prod_id)
{
    this->productController.deleteProduct(prod_id);
}

void GUIProductManager::changeProduct(int id, ProductInfo inf)
{
    Product tmpProduct = this->productController.getProduct(id);
    if (tmpProduct.getID() != NONE)
    {

        tmpProduct.setType(inf.type);

        if (!inf.name.empty())
        {
            tmpProduct.setName(inf.name);
        }

        if (inf.rate > -100)
        {
            tmpProduct.setRate(inf.rate);
        }

        if (inf.min_time > 0)
        {
            tmpProduct.setMinTime(inf.min_time);
        }

        if ((inf.max_time > 0) && (inf.min_time <= inf.max_time))
        {
            tmpProduct.setMaxTime(inf.max_time);
        }

        if (inf.min_sum > 0)
        {
            tmpProduct.setMinSum(inf.min_sum);
        }

        if ((inf.max_sum > 0) && (inf.min_sum <= inf.max_sum))
        {
            tmpProduct.setMaxSum(inf.max_sum);
        }

        tmpProduct.setCurrency(inf.currency);

        this->productController.updateProduct(tmpProduct);
    }
}

float GUIProductManager::round_to(float value, float precision)
{
    return round(value * 10) / 10;
}
