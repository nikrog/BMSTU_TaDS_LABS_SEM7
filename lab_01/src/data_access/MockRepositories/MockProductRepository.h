#ifndef PPO_MOCKPRODUCTREPOSITORY_H
#define PPO_MOCKPRODUCTREPOSITORY_H

#include "../../business_logic/models/ModelProduct.h"
#include "../../business_logic/IRepositories/IProductRepository.h"

class MockProductRepository : public IProductRepository {
private:
    std::vector<Product> products;
public:
    MockProductRepository(std::vector<Product> products): IProductRepository(), products(products) {

    }
    ~MockProductRepository();
    Product getProductByID(int id) override;
    Product getProductByName(std::string name) override;
    std::vector<Product> getProductByRate(Prodtype type, float rate) override;
    std::vector<Product> getProductByBank(Prodtype type, int bank_id) override;
    std::vector<Product> getProductBySum(Prodtype type, float min_sum, float max_sum) override;
    std::vector<Product> getProductByTime(Prodtype type, int min_time, int max_time) override;
    std::vector<Product> getProductByType(Prodtype type) override;
    std::vector<Product> getProductByRating(Prodtype type, float rating) override;
    std::vector<Product> getProductByCurrency(Prodtype type, Curtype currency) override;
    std::vector<Product> getAllProducts() override;
    void updateEl(Product prod_el) override;
    void deleteEl(int id) override;
    int addProduct(ProductInfo inf) override;
};


#endif //PPO_MOCKPRODUCTREPOSITORY_H
