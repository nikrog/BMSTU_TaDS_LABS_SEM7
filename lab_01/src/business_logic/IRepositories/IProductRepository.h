#ifndef PPO_IPRODUCTREPOSITORY_H
#define PPO_IPRODUCTREPOSITORY_H

#include "../models/ModelProduct.h"
#include "CRUDRepository.h"

class IProductRepository : public CRUDRepository<Product> {
public:
    virtual Product getProductByID(int id) = 0;
    virtual Product getProductByName(std::string name) = 0;
    virtual std::vector<Product> getProductByRate(Prodtype type, float rate) = 0;
    virtual std::vector<Product> getProductByBank(Prodtype type, int bank_id) = 0;
    virtual std::vector<Product> getProductBySum(Prodtype type, float min_sum, float max_sum) = 0;
    virtual std::vector<Product> getProductByTime(Prodtype type, int min_time, int max_time) = 0;
    virtual std::vector<Product> getProductByType(Prodtype type) = 0;
    virtual std::vector<Product> getProductByRating(Prodtype type, float rating) = 0;
    virtual std::vector<Product> getProductByCurrency(Prodtype type, Curtype currency) = 0;
    virtual std::vector<Product> getAllProducts() = 0;
    virtual std::vector<Product> filterProducts(ProductFilter f) = 0;
    virtual int addProduct(ProductInfo inf) = 0;
};


#endif //PPO_IPRODUCTREPOSITORY_H
