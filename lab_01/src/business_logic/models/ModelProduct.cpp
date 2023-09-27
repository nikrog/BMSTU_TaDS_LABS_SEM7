#include "ModelProduct.h"

Product::Product(int id, int bank_id, Prodtype type, std::string name, float rate, int min_time, int max_time,
        float min_sum, float max_sum, Curtype currency, int sum_rating, int count_rating){
    this->id = id;
    this->bank_id = bank_id;
    this->type = type;
    this->name = name;
    this->rate = rate;
    this->min_time = min_time;
    this->max_time = max_time;
    this->min_sum = min_sum;
    this->max_sum = max_sum;
    this->currency = currency;
    this->sum_rating = sum_rating;
    this->count_rating = count_rating;
}
Product::Product()
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

Product::~Product()
{}

int Product::getID()
{
    return this->id;
}

int Product::getBankID(){
    return this->bank_id;
}
Prodtype Product::getType()
{
    return this->type;
}
std::string Product::getName()
{
    return this->name;
}
float Product::getRate()
{
    return this->rate;
}
int Product::getMinTime()
{
    return this->min_time;
}
int Product::getMaxTime()
{
    return this->max_time;
}

float Product::getMinSum()
{
    return this->min_sum;
}
float Product::getMaxSum()
{
    return this->max_sum;
}
Curtype Product::getCurrency()
{
    return this->currency;
}
int Product::getSumRating()
{
    return this->sum_rating;
}
int Product::getCountRating()
{
    return this->count_rating;
}
float Product::getAvgRating()
{
    float avg_rating;
    if (this->count_rating > 0)
        avg_rating = (float) this->sum_rating / this->count_rating;
    else
        avg_rating = 0;
    return avg_rating;
}

void Product::setName(std::string name)
{
    this->name = name;
}
void Product::setType(Prodtype type)
{
    this->type = type;
}
void Product::setRate(float rate)
{
    this->rate = rate;
}
void Product::setMinTime(int min_time)
{
    this->min_time = min_time;
}
void Product::setMaxTime(int max_time)
{
    this->max_time = max_time;
}
void Product::setMinSum(float min_sum)
{
    this->min_sum = min_sum;
}
void Product::setMaxSum(float max_sum)
{
    this->max_sum = max_sum;
}
void Product::setCurrency(Curtype currency)
{
    this->currency = currency;
}
void Product::incSumRating(int rating)
{
    this->sum_rating += rating;
}
void Product::incCountRating()
{
    this->count_rating += 1;
}
void Product::setSumRating(int rating)
{
    this->sum_rating = rating;
}
void Product::setCountRating(int count)
{
    this->count_rating = count;
}