#ifndef PPO_PGPRODUCTREPOSITORY_H
#define PPO_PGPRODUCTREPOSITORY_H

#include "../../business_logic/models/ModelProduct.h"
#include "../../business_logic/IRepositories/IProductRepository.h"
#include "../../business_logic/exceptions/exceptions.h"
#include "../commands/PostgresCommands.h"
#include "../connection/connection.h"

class PgProductRepository : public IProductRepository{
private:
    std::string connect_str;
    std::shared_ptr<pqxx::connection> connection;
public:
    PgProductRepository(ConnectionParams params): IProductRepository() {
        this->connect_str = params.getString();
        try
        {
            this->connection = std::make_shared<pqxx::connection>(
                              this->connect_str.c_str());
            if (!this->connection->is_open())
            {
                throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }
    }
    ~PgProductRepository() = default;
    
    Product getProductByID(int id) override;
    Product getProductByName(std::string name) override;
    std::vector<Product> getProductByRate(Prodtype type, float rate) override;
    std::vector<Product> getProductByBank(Prodtype type, int bank_id) override;
    std::vector<Product> getProductBySum(Prodtype type, float min_sum, float max_sum) override;
    std::vector<Product> getProductByTime(Prodtype type, int min_time, int max_time) override;
    std::vector<Product> getProductByType(Prodtype type) override;
    std::vector<Product> getProductByRating(Prodtype type, float rating) override;
    std::vector<Product> getProductByCurrency(Prodtype type, Curtype currency) override;
    std::vector<Product> filterProducts(ProductFilter f) override;
    std::vector<Product> getAllProducts() override;
    void updateEl(Product prod_el) override;
    void deleteEl(int id) override;
    int addProduct(ProductInfo inf) override;
};


#endif //PPO_PGPRODUCTREPOSITORY_H
