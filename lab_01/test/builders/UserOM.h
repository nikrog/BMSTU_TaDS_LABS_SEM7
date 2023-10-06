#ifndef PPO_USEROM_H
#define PPO_USEROM_H

#include "UserBuilder.h"

class UserOM {
    public:
        UserOM();
        ~UserOM();
        UserBuilder guest(int id);
        UserBuilder client(int id);
        UserBuilder manager(int id);
        UserBuilder admin(int id);
};

#endif //PPO_USEROM_H