#ifndef PPO_MANAGERPRINTER_H
#define PPO_MANAGERPRINTER_H

#include <vector>
#include "../../business_logic/models/constants.h"
#include "../../business_logic/models/ModelManager.h"

class ManagerPrinter {
public:
    ManagerPrinter() = default;
    ~ManagerPrinter() = default;
    void printManager(Manager tmpManager);
    //void printAllClients(std::vector<Client> clients);
    void printInputID();
    void printInputBankID();
    void printInputUserID();
    void printInputLogin();
    void printInputPassword();
    void printChangeInfoSuccess();
    void printAddSuccess();
    void printException(const std::exception &e);
};


#endif //PPO_MANAGERPRINTER_H
