#ifndef PPO_PRODUCTGETTER_H
#define PPO_PRODUCTGETTER_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "../../business_logic/exceptions/exceptions.h"
#include "../../business_logic/models/constants.h"

class ProductGetter {
public:
    std::string getString();
    int getInt();
    float getFloat();
    bool check_is_number(std::string req);
};


#endif //PPO_PRODUCTGETTER_H
