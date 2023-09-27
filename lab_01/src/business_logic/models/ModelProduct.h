#ifndef PPO_MODELPRODUCT_H
#define PPO_MODELPRODUCT_H

#include <iostream>
#include <string>
#include "constants.h"

enum Prodtype {
    DEPOSIT = 0,
    CREDIT = 1
};
enum Curtype {
    ROUBLE = 0,
    DOLLAR = 1,
    EURO = 2,
    YUAN = 3
};

class Product {
private:
    int id;
    int bank_id;
    Prodtype type;
    std::string name;
    float rate;
    int min_time;
    int max_time;
    float min_sum;
    float max_sum;
    Curtype currency;
    int sum_rating;
    int count_rating;
public:
    Product(int id, int bank_id, Prodtype type, std::string name, float rate, int min_time, int max_time,
            float min_sum, float max_sum, Curtype currency, int sum_rating, int count_rating);
    Product();
    ~Product();

    int getID();
    int getBankID();
    Prodtype getType();
    std::string getName();
    float getRate();
    int getMinTime();
    int getMaxTime();
    float getMinSum();
    float getMaxSum();
    Curtype getCurrency();
    int getSumRating();
    int getCountRating();
    float getAvgRating();

    void setName(std::string name);
    void setType(Prodtype type);
    void setRate(float rate);
    void setMinTime(int min_time);
    void setMaxTime(int max_time);
    void setMinSum(float min_sum);
    void setMaxSum(float max_sum);
    void setCurrency(Curtype currency);
    void setSumRating(int rating);
    void setCountRating(int count);
    void incSumRating(int rating);
    void incCountRating();
};

struct ProductInfo
{
    int bank_id;
    Prodtype type;
    std::string name;
    float rate;
    int min_time;
    int max_time;
    float min_sum;
    float max_sum;
    Curtype currency;
    int sum_rating;
    int count_rating;
};

struct ProductFilter
{
    int bank_id;
    Prodtype type;
    std::string name;
    float min_rate;
    float max_rate;
    int min_time;
    int max_time;
    float min_sum;
    float max_sum;
    Curtype currency;
    float avg_rating;
    std::string sort_param;
    std::string sort_dir;
};

#endif //PPO_MODELPRODUCT_H
