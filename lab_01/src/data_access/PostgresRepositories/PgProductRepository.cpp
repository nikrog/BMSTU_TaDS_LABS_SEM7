#include "PgProductRepository.h"

Product PgProductRepository::getProductByID(int id)
{
    Product resultProduct;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultProduct = Product(id, result[0][3].as<int>(), Prodtype(result[0][1].as<int>()), result[0][2].as<std::string>(), 
                                   result[0][4].as<float>(), result[0][5].as<int>(),
                                   result[0][6].as<int>(), result[0][7].as<float>(), result[0][8].as<float>(),
                                   Curtype(result[0][9].as<int>()), result[0][10].as<int>(), result[0][11].as<int>());
            }
            else
                resultProduct = Product();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProduct; 
}

Product PgProductRepository::getProductByName(std::string name)
{
    Product resultProduct;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByName().get_str(name);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                resultProduct = Product(result[0][0].as<int>(), result[0][3].as<int>(), Prodtype(result[0][1].as<int>()), 
                                   result[0][2].as<std::string>(), result[0][4].as<float>(), result[0][5].as<int>(),
                                   result[0][6].as<int>(), result[0][7].as<float>(), result[0][8].as<float>(),
                                   Curtype(result[0][9].as<int>()), result[0][10].as<int>(), result[0][11].as<int>());
            }
            else
                resultProduct = Product();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProduct;
}

std::vector<Product> PgProductRepository::getProductByRate(Prodtype type, float rate)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByRate().get_str(type, rate);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(), 
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductByBank(Prodtype type, int bank_id)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByBank().get_str(type, bank_id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductBySum(Prodtype type, float min_sum, float max_sum)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductBySum().get_str(type, min_sum, max_sum);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductByTime(Prodtype type, int min_time, int max_time)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByTime().get_str(type, min_time, max_time);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(), 
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductByType(Prodtype type)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByType().get_str(type);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductByRating(Prodtype type, float rating)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByRating().get_str(type, rating);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getProductByCurrency(Prodtype type, Curtype currency)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetProductByCurrency().get_str(type, currency);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

std::vector<Product> PgProductRepository::getAllProducts()
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllProducts().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(), 
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}


std::vector<Product> PgProductRepository::filterProducts(ProductFilter f)
{
    std::vector<Product> resultProducts = std::vector<Product>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLFilterProducts().get_str(f);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Product currentProd = Product(result[i][0].as<int>(), result[i][3].as<int>(),
                                   Prodtype(result[i][1].as<int>()), result[i][2].as<std::string>(),
                                   result[i][4].as<float>(), result[i][5].as<int>(),
                                   result[i][6].as<int>(), result[i][7].as<float>(), result[i][8].as<float>(),
                                   Curtype(result[i][9].as<int>()), result[i][10].as<int>(), result[i][11].as<int>());
                resultProducts.push_back(currentProd);
            }
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultProducts;
}

void PgProductRepository::updateEl(Product prod_el)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateProduct().get_str(prod_el);
            pqxx::work curConnect(*this->connection);
            curConnect.exec(sql);
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
}

void PgProductRepository::deleteEl(int id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteProduct().get_str(id);
            pqxx::work curConnect(*this->connection);
            curConnect.exec(sql);
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
}

int PgProductRepository::addProduct(ProductInfo inf)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddProduct().get_str(inf);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() == 1)
            {
                res_id = result[0][0].as<int>();
            }
            curConnect.commit();
        }
        else
        {
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
        }
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return res_id;
}
