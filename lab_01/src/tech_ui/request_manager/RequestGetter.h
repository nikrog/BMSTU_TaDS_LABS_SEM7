#ifndef PPO_REQUESTGETTER_H
#define PPO_REQUESTGETTER_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "../../business_logic/exceptions/exceptions.h"
#include "../../business_logic/models/constants.h"

class RequestGetter {
public:
    std::string getString();
    int getInt();
    float getFloat();
    bool check_is_number(std::string req);
};


#endif //PPO_REQUESTGETTER_H
