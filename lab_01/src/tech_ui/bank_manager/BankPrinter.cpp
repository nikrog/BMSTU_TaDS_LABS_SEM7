#include "BankPrinter.h"

void BankPrinter::printBank(Bank bank_el)
{
    std::cout << bank_el.getID() << " " << bank_el.getName() << " номер лицензии - " << bank_el.getLicenseNum() \
              << ", адрес главного офиса - " << bank_el.getAddress() << ", email - " << bank_el.getEmail() \
              << ", телефон - " << bank_el.getPhone() << ", сайт - " << bank_el.getWebsite() << std::endl;
}