#ifndef PPO_ERRORS_H
#define PPO_ERRORS_H

#include <string>

class Error
{
private:
    std::string message;
public:
    Error(std::string message);
    ~Error() = default;
};

#endif //PPO_ERRORS_H
