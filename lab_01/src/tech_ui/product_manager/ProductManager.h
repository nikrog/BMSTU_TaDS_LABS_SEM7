#ifndef PPO_PRODUCTMANAGER_H
#define PPO_PRODUCTMANAGER_H

#include "ProductGetter.h"
#include "ProductPrinter.h"
#include "../../business_logic/rules/ProductRules.h"


class ProductManager {
private:
    ProductRules productController;
    ProductPrinter printer;
    ProductGetter getter;

public:
    ProductManager(ProductRules &pController);
    ProductManager();
    ~ProductManager() = default;
    void viewAllProducts();
    void addProduct();
    void changeProduct();
};


#endif //PPO_PRODUCTMANAGER_H
