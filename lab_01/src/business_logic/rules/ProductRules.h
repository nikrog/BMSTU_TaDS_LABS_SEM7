#ifndef PPO_PRODUCTRULES_H
#define PPO_PRODUCTRULES_H

#include "../models/ModelProduct.h"
#include "../IRepositories/IProductRepository.h"
#include "../models/ModelBank.h"
#include "../IRepositories/IBankRepository.h"
#include "../exceptions/exceptions.h"
#include "ILogger.h"

class ProductRules {
private:
    IProductRepository *repository;
    IBankRepository *bankRepository;
    ILogger *logger;
public:
    ProductRules(IProductRepository &repository, IBankRepository &bankRepository, ILogger &logger);
    ProductRules();
    ~ProductRules();

    Product getProduct(int id);
    Product getProductByName(std::string name);
    std::vector<Product> getProductByRate(Prodtype ptype, float rate);
    std::vector<Product> getProductByBank(Prodtype ptype, int bank_id);
    std::vector<Product> getProductBySum(Prodtype ptype, float min_sum, float max_sum);
    std::vector<Product> getProductByTime(Prodtype ptype, int min_time, int max_time);
    std::vector<Product> getProductByType(Prodtype ptype);
    std::vector<Product> getProductByRating(Prodtype ptype, float rating);
    std::vector<Product> getProductByCurrency(Prodtype ptype, Curtype currency);
    std::vector<Product> filterProducts(ProductFilter f);
    void updateProduct(Product prod_el);
    void deleteProduct(int id);
    int addProduct(ProductInfo inf);
    std::vector<Product> getAllProducts();
};


#endif //PPO_PRODUCTRULES_H
