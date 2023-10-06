#ifndef PPO_MODELCLIENT_H
#define PPO_MODELCLIENT_H

#include "constants.h"
#include <iostream>
#include <string>

typedef long int passport_t;

class Client {
private:
    int id;
    int user_id;
    std::string name;
    std::string surname;
    std::string patronymic;
    passport_t passport_num;
    date_t birth_date;
    std::string address;
    std::string email;
    std::string phone;
public:
    Client(int id, int user_id, std::string name, std::string surname, std::string patronymic, passport_t passport_num,
           date_t birth_date, std::string address, std::string email, std::string phone);
    Client();
    ~Client();

    int getID();
    int getUserID();
    passport_t getPassportNum();
    date_t getBirthDate();
    std::string getName();
    std::string getSurname();
    std::string getPatronymic();
    std::string getAddress();
    std::string getEmail();
    std::string getPhone();

    void setName(std::string name);
    void setSurname(std::string surname);
    void setPatronymic(std::string patronymic);
    void setAddress(std::string address);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setPassportNum(passport_t passport_num);
    void setBirthDate(date_t birth_date);
};

struct FIO {
    std::string name;
    std::string surname;
    std::string patronymic;
};

struct ClientInfo {
    int user_id;
    std::string name;
    std::string surname;
    std::string patronymic;
    passport_t passport_num;
    date_t birth_date;
    std::string address;
    std::string email;
    std::string phone;
};

#endif //PPO_MODELCLIENT_H
