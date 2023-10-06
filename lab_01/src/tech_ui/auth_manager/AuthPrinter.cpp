#include "AuthPrinter.h"

void AuthPrinter::print_login_entry() {
    std::cout << LOGIN_INPUT_MESSAGE;
}

void AuthPrinter::print_password_entry() {
    std::cout << PASSWORD_INPUT_MESSAGE;
}

void AuthPrinter::print_success() {
    std::cout << AUTH_SUCCESS;
}

void AuthPrinter::print_error_login()
{
    std::cout << LOGIN_ERROR;
}

void AuthPrinter::print_error_password()
{
    std::cout << PASSWORD_ERROR;
}

void AuthPrinter::printException(const std::exception &e)
{
    std::cout << e.what() << std::endl;
}