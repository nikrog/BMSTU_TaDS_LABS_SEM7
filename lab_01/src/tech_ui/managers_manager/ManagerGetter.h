#ifndef PPO_MANAGERGETTER_H
#define PPO_MANAGERGETTER_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "../../business_logic/exceptions/exceptions.h"
#include "../../business_logic/models/constants.h"

class ManagerGetter {
public:
    int getInt();
    bool check_is_number(std::string req);
    std::string getString();
};


#endif //PPO_MANAGERGETTER_H
