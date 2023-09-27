#ifndef PPO_COMMANDS_H
#define PPO_COMMANDS_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

enum CMD_KEYS {
    EXIT,
    UN_AUTH,
    AUTH,
    ADD_CLIENT,
    ADD_MANAGER,
    VIEW_CLIENT,
    VIEW_ALL_CLIENTS,
    VIEW_ALL_PRODUCTS,
    ADD_PRODUCT,
    VIEW_ALL_REQUESTS,
    MAKE_REQUEST,
    VIEW_MY_REQUESTS,
    CONFIRM_REQUEST,
    REJECT_REQUEST,
    RATE_PRODUCT,
    VIEW_ALL_BANKS,
    UPDATE_PRODUCT,
    NOT_A_COMMAND
};

class CommandHandler {
private:
    bool check_is_number(std::string cmd);
public:
    CommandHandler() = default;
    ~CommandHandler() = default;
    CMD_KEYS handle(std::string cmd);
};


#endif //PPO_COMMANDS_H
