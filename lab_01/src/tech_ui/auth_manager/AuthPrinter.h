#ifndef PPO_AUTHPRINTER_H
#define PPO_AUTHPRINTER_H

#include <iostream>
#include <string>
#include "../../business_logic/models/constants.h"


class AuthPrinter {
public:
    AuthPrinter() = default;
    ~AuthPrinter() = default;
    void print_login_entry();
    void print_password_entry();
    void print_error_login();
    void print_error_password();
    void print_success();
    void printException(const std::exception &e);
};


#endif //PPO_AUTHPRINTER_H
