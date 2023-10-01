#ifndef PPO_STUBDATA_H
#define PPO_STUBDATA_H

#include "../../src/business_logic/models/ModelManager.h"
#include "../../src/business_logic/models/ModelUser.h"
#include "../../src/business_logic/models/ModelClient.h"
#include "../../src/business_logic/models/ModelBank.h"
#include "../../src/business_logic/models/ModelProduct.h"
#include "../../src/business_logic/models/ModelRequest.h"

class StubData {   
    public:
        std::vector<User> users = {User(1, "user1", "12345", CLIENT), 
        User(2, "user2", "12345", MANAGER),
        User(3, "user3", "12345", CLIENT),
        User(4, "user4", "12345", ADMIN),
        User(5, "user2", "12345", MANAGER)};
        std::vector<Bank> banks = {Bank(1, "VTB", 1234, "Street 9", "vtb@vtb.ru", "+749567890555", "vtb.ru"),
        Bank(2, "Sber", 1235, "Street 78", "sber@sber.ru", "+749567890777", "sber.ru")};
        std::vector<Manager> managers = {Manager(1, 2, 1), Manager(2, 5, 2)};
        std::vector<Client> clients = {Client(1, 1, "a", "a", "a", 77777, 1980, "Street 8", "a@mail.ru", "+79183456780"),
        Client(2, 3, "b", "b", "b", 77779, 1986, "Street 9", "b@mail.ru", "+79183456781")};
        std::vector<Product> products = {Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0),
        Product(2, 2, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0)};
        std::vector<Request> requests = {Request(1, 1, 1, NONE, 100000, 365, 2023, OPENED),
        Request(2, 2, 2, 1, 100000, 365, 2023, APPROVED)};
};

#endif //PPO_STUBDATA_H