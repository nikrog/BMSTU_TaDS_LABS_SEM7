#include "ClientBuilder.h"

ClientBuilder::ClientBuilder()
{
    this->id = NONE;
    this->user_id = NONE;
    this->name = EMPTY;
    this->surname = EMPTY;
    this->patronymic = EMPTY;
    this->passport_num = NONE;
    this->birth_date = DEF_TIME;
    this->address = EMPTY;
    this->email = EMPTY;
    this->phone = EMPTY;
}

ClientBuilder::~ClientBuilder()
{}

ClientBuilder& ClientBuilder::withId(int id)
{
    this->id = id;
    return *this;
}

ClientBuilder& ClientBuilder::withUser(int user_id)
{
    this->user_id = user_id;
    return *this;
}

ClientBuilder& ClientBuilder::withName(std::string name)
{
    this->name = name;
    return *this;
}

ClientBuilder& ClientBuilder::withSurname(std::string surname)
{
    this->surname = surname;
    return *this;
}

ClientBuilder& ClientBuilder::withPatronymic(std::string patronymic)
{
    this->patronymic = patronymic;
    return *this;
}

ClientBuilder& ClientBuilder::withPassport(passport_t passport_num)
{
    this->passport_num = passport_num;
    return *this;
}

ClientBuilder& ClientBuilder::withBirthDate(date_t birth_date)
{
    this->birth_date = birth_date;
    return *this;
}

ClientBuilder& ClientBuilder::withAddress(std::string address)
{
    this->address = address;
    return *this;
}

ClientBuilder& ClientBuilder::withEmail(std::string email)
{
    this->email = email;
    return *this;
}

ClientBuilder& ClientBuilder::withPhone(std::string phone)
{
    this->phone = phone;
    return *this;
}

Client ClientBuilder::build()
{
    Client cl = Client(this->id, this->user_id, this->name, this->surname, this->patronymic, this->passport_num,
    this->birth_date, this->address, this->email, this->phone);
    return cl;
}

