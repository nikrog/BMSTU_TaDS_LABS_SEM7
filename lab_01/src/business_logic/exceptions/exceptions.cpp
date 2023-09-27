#include "exceptions.h"

BaseException::BaseException(std::string fileName, std::string className,
                             int currentLine, std::string information)
{
    this->info = information;
}

const char *BaseException::what() const noexcept
{
    const char *result = info.c_str();
    return result;
}
