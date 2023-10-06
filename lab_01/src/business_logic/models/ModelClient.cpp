#include "ModelClient.h"

Client::Client(int id, int user_id, std::string name, std::string surname, std::string patronymic, passport_t passport_num,
       date_t birth_date, std::string address, std::string email, std::string phone){

    this->id = id;
    this->user_id = user_id;
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->passport_num = passport_num;
    this->birth_date = birth_date;
    this->address = address;
    this->email = email;
    this->phone = phone;
}

Client::Client()
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

Client::~Client()
{}

int Client::getID(){
    return this->id;
}

int Client::getUserID(){
    return this->user_id;
}

date_t Client::getBirthDate(){
    return this->birth_date;
}

passport_t Client::getPassportNum(){
    return this->passport_num;
}

std::string Client::getName(){
    return this->name;
}

std::string Client::getSurname(){
    return this->surname;
}

std::string Client::getPatronymic(){
    return this->patronymic;
}

std::string Client::getAddress(){
    return this->address;
}

std::string Client::getEmail(){
    return this->email;
}

std::string Client::getPhone()
{
    return this->phone;
}

void Client::setName(std::string name){
    this->name = name;
}

void Client::setSurname(std::string surname){
    this->surname = surname;
}

void Client::setPatronymic(std::string patronymic){
    this->patronymic = patronymic;
}

void Client::setAddress(std::string address){
    this->address = address;
}

void Client::setEmail(std::string email){
    this->email = email;
}

void Client::setPhone(std::string phone){
    this->phone = phone;
}

void Client::setPassportNum(passport_t passport_num){
    this->passport_num = passport_num;
}

void Client::setBirthDate(date_t birth_date) {
    this->birth_date = birth_date;
}
