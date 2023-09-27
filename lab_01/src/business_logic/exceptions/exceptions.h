#ifndef PPO_EXCEPTIONS_H
#define PPO_EXCEPTIONS_H

#include <exception>
#include <iostream>
#include "../models/constants.h"

class BaseException: public std::exception
{
public:
    BaseException(std::string fileName, std::string className,
                  int currentLine,
                  std::string information);

    virtual const char *what() const noexcept override;

protected:
    std::string info;
};

class UserNotFoundException : public BaseException
{
public:
    UserNotFoundException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = USER_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};


class UserAddErrorException : public BaseException
{
public:
    UserAddErrorException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = USER_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class UserDeleteErrorException : public BaseException
{
public:
    UserDeleteErrorException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = USER_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class UserUpdateErrorException : public BaseException
{
public:
    UserUpdateErrorException(std::string filename, std::string classname,
    int number_of_line,
            std::string information = USER_UPDATE_ERROR):
    BaseException(filename, classname, number_of_line, information) {};

};

class ManagerNotFoundException : public BaseException
{
public:
    ManagerNotFoundException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = MANAGER_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ManagerAddErrorException : public BaseException
{
public:
    ManagerAddErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = MANAGER_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ManagerUpdateErrorException : public BaseException
{
public:
    ManagerUpdateErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = MANAGER_UPDATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ManagerDeleteErrorException : public BaseException
{
public:
    ManagerDeleteErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = MANAGER_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class BankNotFoundException : public BaseException
{
public:
    BankNotFoundException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = BANK_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class BankAddErrorException : public BaseException
{
public:
    BankAddErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = BANK_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class BankUpdateErrorException : public BaseException
{
public:
    BankUpdateErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = BANK_UPDATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class BankDeleteErrorException : public BaseException
{
public:
    BankDeleteErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = BANK_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};
class ClientNotFoundException : public BaseException
{
public:
    ClientNotFoundException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = CLIENT_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ClientAddErrorException : public BaseException
{
public:
    ClientAddErrorException(std::string filename, std::string classname,
                          int number_of_line,
                          std::string information = CLIENT_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ClientUpdateErrorException : public BaseException
{
public:
    ClientUpdateErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = CLIENT_UPDATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ClientDeleteErrorException : public BaseException
{
public:
    ClientDeleteErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = CLIENT_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductNotFoundException : public BaseException
{
public:
    ProductNotFoundException(std::string filename, std::string classname,
                            int number_of_line,
                            std::string information = PRODUCT_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductAddErrorException : public BaseException
{
public:
    ProductAddErrorException(std::string filename, std::string classname,
                            int number_of_line,
                            std::string information = PRODUCT_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductUpdateErrorException : public BaseException
{
public:
    ProductUpdateErrorException(std::string filename, std::string classname,
                               int number_of_line,
                               std::string information = PRODUCT_UPDATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductDeleteErrorException : public BaseException
{
public:
    ProductDeleteErrorException(std::string filename, std::string classname,
                               int number_of_line,
                               std::string information = PRODUCT_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductGetErrorException : public BaseException
{
public:
    ProductGetErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = PRODUCT_GET_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestNotFoundException : public BaseException
{
public:
    RequestNotFoundException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = REQUEST_NOT_FOUND_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestAddErrorException : public BaseException
{
public:
    RequestAddErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = REQUEST_ADD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestUpdateErrorException : public BaseException
{
public:
    RequestUpdateErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = REQUEST_UPDATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestDeleteErrorException : public BaseException
{
public:
    RequestDeleteErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = REQUEST_DELETE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestGetErrorException : public BaseException
{
public:
    RequestGetErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = REQUEST_GET_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestMakeErrorException : public BaseException
{
public:
    RequestMakeErrorException(std::string filename, std::string classname,
                                 int number_of_line,
                                 std::string information = REQUEST_MAKE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestConfirmErrorException : public BaseException
{
public:
    RequestConfirmErrorException(std::string filename, std::string classname,
                             int number_of_line,
                             std::string information = REQUEST_CONFIRM_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class RequestRejectErrorException : public BaseException
{
public:
    RequestRejectErrorException(std::string filename, std::string classname,
                                 int number_of_line,
                                 std::string information = REQUEST_REJECT_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class ProductRateErrorException : public BaseException
{
public:
    ProductRateErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = PRODUCT_RATE_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};


class DatabaseConnectException : public BaseException
{
public:
    DatabaseConnectException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = DATABASE_CONNECT_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class IncorrectPasswordException : public BaseException
{
public:
    IncorrectPasswordException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = PASSWORD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class LoginNotFoundException : public BaseException
{
public:
    LoginNotFoundException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = LOGIN_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class IncorrectPasswordOrLoginException : public BaseException
{
public:
    IncorrectPasswordOrLoginException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = LOGIN_OR_PASSWORD_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class InputIntErrorException : public BaseException
{
public:
    InputIntErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = INPUT_INT_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

class InputFloatErrorException : public BaseException
{
public:
    InputFloatErrorException(std::string filename, std::string classname,
                                int number_of_line,
                                std::string information = INPUT_FLOAT_ERROR):
            BaseException(filename, classname, number_of_line, information) {};

};

#endif //PPO_EXCEPTIONS_H
