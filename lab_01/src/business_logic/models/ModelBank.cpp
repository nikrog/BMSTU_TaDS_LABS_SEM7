#include "ModelBank.h"

Bank::Bank(int id, std::string name, license_t license_num, std::string address, std::string email,
     std::string phone, std::string website){
    this->id = id;
    this->name = name;
    this->license_num = license_num;
    this->address = address;
    this->email = email;
    this->phone = phone;
    this->website = website;
}
Bank::Bank(){
    this->id = NONE;
    this->name = EMPTY;
    this->license_num = NONE;
    this->address = EMPTY;
    this->email = EMPTY;
    this->phone = EMPTY;
    this->website = EMPTY;
}

Bank::~Bank()
{}

int Bank::getID()
{
    return this->id;
}

license_t Bank::getLicenseNum()
{
    return this->license_num;
}
std::string Bank::getName()
{
    return this->name;
}
std::string Bank::getAddress()
{
    return this->address;
}
std::string Bank::getEmail()
{
    return this->email;
}
std::string Bank::getPhone()
{
    return this->phone;
}
std::string Bank::getWebsite()
{
    return this->website;
}

void Bank::setName(std::string name)
{
    this->name = name;
}
void Bank::setAddress(std::string address)
{
    this->address = address;
}
void Bank::setEmail(std::string email)
{
    this->email = email;
}
void Bank::setPhone(std::string phone)
{
    this->phone = phone;
}
void Bank::setWebsite(std::string website)
{
    this->website = website;
}
void Bank::setLicenseNum(license_t license_num)
{
    this->license_num = license_num;
}