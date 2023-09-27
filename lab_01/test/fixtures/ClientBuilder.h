#ifndef PPO_CLIENTBUILDER_H
#define PPO_CLIENTBUILDER_H

#include "../../src/business_logic/models/ModelClient.h"
#include "../../src/business_logic/rules/ClientRules.h"

class ClientBuilder {
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
        ClientBuilder();
        ~ClientBuilder();
        ClientBuilder& withId(int id);
        ClientBuilder& withUser(int user_id);
        ClientBuilder& withName(std::string name);
        ClientBuilder& withSurname(std::string surname);
        ClientBuilder& withPatronymic(std::string patronymic);
        ClientBuilder& withPassport(passport_t passport_num);
        ClientBuilder& withBirthDate(date_t birth_date);
        ClientBuilder& withAddress(std::string address);
        ClientBuilder& withEmail(std::string email);
        ClientBuilder& withPhone(std::string phone);
        Client build();
};

#endif //PPO_PRODUCTBUILDER_H