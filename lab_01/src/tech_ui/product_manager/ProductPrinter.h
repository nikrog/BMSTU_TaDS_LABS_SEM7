#ifndef PPO_PRODUCTPRINTER_H
#define PPO_PRODUCTPRINTER_H

#include <iostream>
#include <string>
#include "../../business_logic/models/ModelProduct.h"
#include "../../business_logic/models/constants.h"

class ProductPrinter {
public:
    ProductPrinter() = default;
    ~ProductPrinter() = default;
    void printProduct(Product prod_el);
    void printInputID();
    void printInputBankID();
    void printInputType();
    void printInputName();
    void printInputRate();
    void printInputMinTime();
    void printInputMaxTime();
    void printInputMinSum();
    void printInputMaxSum();
    void printInputCurrency();
    void printInputScore();
    void printAddSuccess();
    void printException(const std::exception &e);
};


#endif //PPO_PRODUCTPRINTER_H
