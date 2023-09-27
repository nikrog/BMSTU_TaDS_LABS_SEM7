#ifndef PPO_MODELBANK_H
#define PPO_MODELBANK_H

#include "constants.h"
#include <iostream>
#include <string>

typedef int license_t;

class Bank {
private:
    int id;
    std::string name;
    license_t license_num;
    std::string address;
    std::string email;
    std::string phone;
    std::string website;
public:
    Bank(int id, std::string name, license_t license_num, std::string address, std::string email,
           std::string phone, std::string website);
    Bank();
    ~Bank();

    int getID();
    license_t getLicenseNum();
    std::string getName();
    std::string getAddress();
    std::string getEmail();
    std::string getPhone();
    std::string getWebsite();

    void setName(std::string name);
    void setAddress(std::string address);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setWebsite(std::string website);
    void setLicenseNum(license_t license_num);
};

struct BankInfo {
    std::string name;
    license_t license_num;
    std::string address;
    std::string email;
    std::string phone;
    std::string website;
};
#endif //PPO_MODELBANK_H
