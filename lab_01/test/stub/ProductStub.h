#ifndef PPO_PRODUCTSTUB_H
#define PPO_PRODUCTSTUB_H

#include "../../src/business_logic/IRepositories/IProductRepository.h"
#include "../../src/business_logic/models/ModelProduct.h"

class ProductStub : public IProductRepository {   
    private:
        std::vector<Product> products;
    public:
        ProductStub(): IProductRepository() {
            std::vector<Product> p = {Product(1, 1, DEPOSIT, "first", 7.5, 180, 750,  50000, 1000000, ROUBLE, 0, 0),
                Product(2, 2, CREDIT, "second", 7.5, 180, 750,  50000, 1000000, DOLLAR, 0, 0)};
            this->products = p;
        }
        ~ProductStub();
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
        std::vector<Product> filterProducts(ProductFilter f) override;
        void updateEl(Product prod_el) override;
        void deleteEl(int id) override;
        int addProduct(ProductInfo inf) override;
};

#endif //PPO_PRODUCTSTUB_H