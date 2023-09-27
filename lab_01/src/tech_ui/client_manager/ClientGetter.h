#ifndef PPO_CLIENTGETTER_H
#define PPO_CLIENTGETTER_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "../../business_logic/models/constants.h"
#include "../../business_logic/exceptions/exceptions.h"

class ClientGetter {
public:
    std::string getString();
    int getInt();
    bool check_is_number(std::string req);
};


#endif //PPO_CLIENTGETTER_H
