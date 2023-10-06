#include "BankOM.h"

BankOM::BankOM()
{}

BankOM::~BankOM()
{}

BankBuilder BankOM::filledBank(int id)
{
    char buf1[50], buf2[50], buf3[50], buf4[50], buf5[50];
    auto fmt1 = "bank%d", fmt2 = "address%d", fmt3 = "email%d", fmt4 = "phone%d", fmt5 = "website%d";
    std::snprintf(buf1, 50, fmt1, id);
    std::snprintf(buf2, 50, fmt2, id);
    std::snprintf(buf3, 50, fmt3, id);
    std::snprintf(buf4, 50, fmt4, id);
    std::snprintf(buf5, 50, fmt5, id);
    std::string name(buf1);
    std::string address(buf2);
    std::string email(buf3);
    std::string phone(buf4);
    std::string website(buf5);
    BankBuilder obj = BankBuilder().withId(id).withName(name).withLicenceNum(id).withAddress(address).withEmail(email).withPhone(phone)\
    .withWebsite(website);
    return obj;
}