#include "BankBuilder.h"

BankBuilder::BankBuilder()
{
    this->id = NONE;
    this->name = EMPTY;
    this->license_num = NONE;
    this->address = EMPTY;
    this->email = EMPTY;
    this->phone = EMPTY;
    this->website = EMPTY;
}

BankBuilder::~BankBuilder()
{}

BankBuilder& BankBuilder::withId(int id)
{
    this->id = id;
    return *this;
}

BankBuilder& BankBuilder::withName(std::string name)
{
    this->name = name;
    return *this;
}

BankBuilder& BankBuilder::withLicenceNum(license_t license_num)
{
    this->license_num = license_num;
    return *this;
}

BankBuilder& BankBuilder::withAddress(std::string address)
{
    this->address = address;
    return *this;
}

BankBuilder& BankBuilder::withEmail(std::string email)
{
    this->email = email;
    return *this;
}

BankBuilder& BankBuilder::withPhone(std::string phone)
{
    this->phone = phone;
    return *this;
}

BankBuilder& BankBuilder::withWebsite(std::string website)
{
    this->website = website;
    return *this;
}

Bank BankBuilder::build()
{
    Bank bn = Bank(this->id, this->name, this->license_num, this->address, this->email, this->phone, this->website);
    return bn;
}