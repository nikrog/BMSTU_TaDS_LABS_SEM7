#ifndef PPO_PRODUCTBUILDER_H
#define PPO_PRODUCTBUILDER_H

#include "../../src/business_logic/models/ModelProduct.h"
#include "../../src/business_logic/rules/ProductRules.h"

class ProductBuilder {
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
        ProductBuilder();
        ~ProductBuilder();
        ProductBuilder& withId(int id);
        ProductBuilder& withBank(int bank_id);
        ProductBuilder& withType(Prodtype type);
        ProductBuilder& withName(std::string name);
        ProductBuilder& withRate(float rate);
        ProductBuilder& withMinTime(int min_time);
        ProductBuilder& withMaxTime(int max_time);
        ProductBuilder& withMinSum(float min_sum);
        ProductBuilder& withMaxSum(float max_sum);
        ProductBuilder& withCurrency(Curtype currency);
        ProductBuilder& withSumRating(int sum_rating);
        ProductBuilder& withCountRating(int count_rating);
        Product build();
};

#endif //PPO_PRODUCTBUILDER_H