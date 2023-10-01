#include "ProductOM.h"

ProductOM::ProductOM()
{}

ProductOM::~ProductOM()
{}

ProductBuilder ProductOM::filledProduct(int id)
{
    char buf1[50];
    auto fmt1 = "product%d";
    std::snprintf(buf1, 50, fmt1, id);
    std::string name(buf1);
    ProductBuilder obj = ProductBuilder().withId(id).withName(name).withMinTime(id).withMaxTime(id + 10).withMinSum(id)\
    .withMaxSum(id + 1000);
    return obj;
}