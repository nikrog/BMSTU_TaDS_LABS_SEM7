#ifndef PPO_AUTHSTATES_H
#define PPO_AUTHSTATES_H

#include "../../business_logic/models/ModelUser.h"

class AuthStates {
private:
    Roles appState;

public:
    AuthStates();
    ~AuthStates() = default;
    Roles getState();
    void toClientAuth();
    void toManagerAuth();
    void toAdminAuth();
    void toUnAuth();
    bool isUnAuth();
    bool isManagerAuth();
    bool isClientAuth();
    bool isAdminAuth();
};


#endif //PPO_AUTHSTATES_H
