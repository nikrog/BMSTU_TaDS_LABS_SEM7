#ifndef PPO_PRODUCTOM_H
#define PPO_PRODUCTOM_H

#include "ProductBuilder.h"

class ProductOM {
    public:
        ProductOM();
        ~ProductOM();
        ProductBuilder filledProduct(int id);
};

#endif //PPO_BANKOM_H