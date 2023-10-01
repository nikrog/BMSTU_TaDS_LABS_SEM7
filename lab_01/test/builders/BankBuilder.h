#ifndef PPO_BANKBUILDER_H
#define PPO_BANKBUILDER_H

#include "../../src/business_logic/models/ModelBank.h"
#include "../../src/business_logic/rules/BankRules.h"

class BankBuilder {
    private:
        int id;
        std::string name;
        license_t license_num;
        std::string address;
        std::string email;
        std::string phone;
        std::string website;

    public:
        BankBuilder();
        ~BankBuilder();
        BankBuilder& withId(int id);
        BankBuilder& withName(std::string name);
        BankBuilder& withLicenceNum(license_t license_num);
        BankBuilder& withAddress(std::string address);
        BankBuilder& withEmail(std::string email);
        BankBuilder& withPhone(std::string phone);
        BankBuilder& withWebsite(std::string website);
        Bank build();
};

#endif //PPO_BANKBUILDER_H