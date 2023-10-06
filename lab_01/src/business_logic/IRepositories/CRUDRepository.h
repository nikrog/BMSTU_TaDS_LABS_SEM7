#ifndef PPO_CRUDREPOSITORY_H
#define PPO_CRUDREPOSITORY_H

#include <vector>

template<typename T>
class CRUDRepository {
public:
    virtual void updateEl(T element) = 0;
    virtual void deleteEl(int id) = 0;
};

#endif //PPO_CRUDREPOSITORY_H
