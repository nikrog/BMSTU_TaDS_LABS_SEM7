#include "ProductGetter.h"

std::string ProductGetter::getString()
{
    std::string result;
    std::cin >> result;
    return result;
}

bool ProductGetter::check_is_number(std::string req)
{
    return !req.empty() && std::all_of(req.begin(), req.end(), ::isdigit);
}

int ProductGetter::getInt()
{
    std::string str;
    int result = NONE;
    std::cin >> str;
    if (check_is_number(str))
        result = std::stoi(str);
    else
        throw InputIntErrorException(__FILE__, typeid(*this).name(), __LINE__);
    return result;
}

float ProductGetter::getFloat()
{
    std::string str;
    float result = 0;
    std::cin >> str;
    result = std::stof(str);
    /*try
    {
        if (!str.empty())
            result = std::stof(str);
        else
            throw InputFloatErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }*/

    return result;
}