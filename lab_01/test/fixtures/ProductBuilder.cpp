#include "ProductBuilder.h"

ProductBuilder::ProductBuilder()
{
    this->id = NONE;
    this->bank_id = NONE;
    this->type = DEPOSIT;
    this->name = EMPTY;
    this->rate = 0;
    this->min_time = 0;
    this->max_time = 1;
    this->min_sum = 0;
    this->max_sum = 1;
    this->currency = ROUBLE;
    this->sum_rating = 0;
    this->count_rating = 0;
}

ProductBuilder::~ProductBuilder()
{}

ProductBuilder& ProductBuilder::withId(int id)
{
    this->id = id;
    return *this;
}

ProductBuilder& ProductBuilder::withBank(int bank_id)
{
    this->bank_id = bank_id;
    return *this;
}

ProductBuilder& ProductBuilder::withType(Prodtype type)
{
    this->type = type;
    return *this;
}

ProductBuilder& ProductBuilder::withName(std::string name)
{
    this->name = name;
    return *this;
}

ProductBuilder& ProductBuilder::withRate(float rate)
{
    this->rate = rate;
    return *this;
}

ProductBuilder& ProductBuilder::withMinTime(int min_time)
{
    this->min_time = min_time;
    return *this;
}

ProductBuilder& ProductBuilder::withMaxTime(int max_time)
{
    this->max_time = max_time;
    return *this;
}

ProductBuilder& ProductBuilder::withMinSum(float min_sum)
{
    this->min_sum = min_sum;
    return *this;
}

ProductBuilder& ProductBuilder::withMaxSum(float max_sum)
{
    this->max_sum = max_sum;
    return *this;
}
ProductBuilder& ProductBuilder::withCurrency(Curtype currency)
{
    this->currency = currency;
    return *this;
}

ProductBuilder& ProductBuilder::withSumRating(int sum_rating)
{
    this->sum_rating = sum_rating;
    return *this;
}

ProductBuilder& ProductBuilder::withCountRating(int count_rating)
{
    this->count_rating = count_rating;
    return *this;
}

Product ProductBuilder::build()
{
    Product prod = Product(this->id, this->bank_id, this->type, this->name, this->rate, this->min_time,
    this->max_time, this->min_sum, this->max_sum, this->currency, this->sum_rating, this->count_rating);
    return prod;
}