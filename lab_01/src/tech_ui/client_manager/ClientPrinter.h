#ifndef PPO_CLIENTPRINTER_H
#define PPO_CLIENTPRINTER_H

#include <vector>
#include "../../business_logic/models/constants.h"
#include "../../business_logic/models/ModelClient.h"

class ClientPrinter {
public:
    ClientPrinter() = default;
    ~ClientPrinter() = default;
    void printClient(Client tmpClient);
    void printAllClients(std::vector<Client> clients);
    void printInputID();
    void printInputName();
    void printInputSurname();
    void printInputPatronymic();
    void printInputPassportNum();
    void printInputEmail();
    void printInputBirthDate();
    void printInputAddress();
    void printInputPhone();
    void printInputLogin();
    void printInputPassword();
    void printChangeInfoSuccess();
    void printException(const std::exception &e);
};


#endif //PPO_CLIENTPRINTER_H
