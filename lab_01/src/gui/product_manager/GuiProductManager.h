#ifndef PPO_GUIPRODUCTMANAGER_H
#define PPO_GUIPRODUCTMANAGER_H

#include "../../business_logic/rules/ProductRules.h"
#include <cmath>

class GUIProductManager {
private:
    ProductRules productController;

public:
    GUIProductManager(ProductRules &pController);
    GUIProductManager();
    ~GUIProductManager() = default;
    std::vector<Product> viewAllProducts();
    std::vector<Product> viewProductsByType(Prodtype t);
    std::vector<Product> viewFilterProducts(ProductFilter f);
    Product viewProduct(int id);
    void addProduct(ProductInfo inf);
    void deleteProduct(int prod_id);
    void changeProduct(int id, ProductInfo inf);
    float round_to(float value, float precision);
};


#endif //PPO_GUIPRODUCTMANAGER_H
