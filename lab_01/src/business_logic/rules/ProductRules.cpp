#include "ProductRules.h"


ProductRules::ProductRules(IProductRepository &repository, IBankRepository &bankRepository, ILogger &logger)
{
    this->repository = &repository;
    this->bankRepository = &bankRepository;
    this->logger = &logger;
}
ProductRules::ProductRules()
{}
ProductRules::~ProductRules()
{}

Product ProductRules::getProduct(int id) {
    Product tmpProduct = this->repository->getProductByID(id);
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Product not found");
        throw ProductNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get product success");
        return tmpProduct;
    }
}

Product ProductRules::getProductByName(std::string name)
{
    Product tmpProduct = this->repository->getProductByName(name);
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Product not found");
        throw ProductNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
    else
    {
        this->logger->log(INFO, "Get product by name success");
        return tmpProduct;
    }
}

std::vector<Product> ProductRules::getProductByRate(Prodtype ptype, float rate)
{
    if ((ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductByRate(ptype, rate);
    this->logger->log(INFO, "Get product by rate success");
    return products;
}

std::vector<Product> ProductRules::getProductByBank(Prodtype ptype, int bank_id)
{
    if ((ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Bank> banks = this->bankRepository->getAllBanks();
    int id = NONE;
    for (size_t i = 0; i < banks.size(); i++)
        if (banks[i].getID() == bank_id)
            id = banks[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Product get error (bank not found)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductByBank(ptype, bank_id);
    this->logger->log(INFO, "Get product by bank success");
    return products;
}

std::vector<Product> ProductRules::getProductBySum(Prodtype ptype, float min_sum, float max_sum)
{
    if ((min_sum < MIN_SUM) || (max_sum < MIN_SUM) || (min_sum > max_sum) || (ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product sum or type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductBySum(ptype, min_sum, max_sum);
    this->logger->log(INFO, "Get product by sum success");
    return products;
}

std::vector<Product> ProductRules::getProductByTime(Prodtype ptype, int min_time, int max_time)
{
    if ((min_time < MIN_TIME) || (max_time < MIN_TIME) || (min_time > max_time) || (ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product duration or type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductByTime(ptype, min_time, max_time);
    this->logger->log(INFO, "Get product by time success");
    return products;
}

std::vector<Product> ProductRules::getProductByType(Prodtype ptype)
{
    if ((ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductByType(ptype);
    this->logger->log(INFO, "Get product by type success");
    return products;
}

std::vector<Product> ProductRules::getProductByRating(Prodtype ptype, float rating)
{
    if ((rating < 0) || (ptype < DEPOSIT) || (ptype > CREDIT))
    {
        this->logger->log(ERROR, "Product get error (incorrect product rating or type)");
        throw ProductGetErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Product> products = this->repository->getProductByRating(ptype, rating);
    this->logger->log(INFO, "Get product by rating success");
    return products;
}

std::vector<Product> ProductRules::getProductByCurrency(Prodtype ptype, Curtype currency)
{
    std::vector<Product> products = this->repository->getProductByCurrency(ptype, currency);
    this->logger->log(INFO, "Get product by currency success");
    return products;
}

std::vector<Product> ProductRules::filterProducts(ProductFilter f)
{
    std::vector<Product> products = this->repository->filterProducts(f);
    this->logger->log(INFO, "Filter products by params success");
    return products;
}

void ProductRules::updateProduct(Product prod_el)
{
    if ((prod_el.getName().length() < 1) || (prod_el.getMinTime() < MIN_TIME) || (prod_el.getMaxTime() < MIN_TIME)
    || (prod_el.getMinTime() > prod_el.getMaxTime()) || (prod_el.getMinSum() < MIN_SUM)
    || (prod_el.getMaxSum() < MIN_SUM) || (prod_el.getMinSum() > prod_el.getMaxSum()) || (prod_el.getCountRating() < 0)
    || (prod_el.getCurrency() < ROUBLE) || (prod_el.getCurrency() > YUAN) || (prod_el.getType() < DEPOSIT)
    || (prod_el.getType() > CREDIT) || (prod_el.getSumRating() < 0))
    {
        this->logger->log(ERROR, "Product update error (inavalid params)");
        throw ProductUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Bank> banks = this->bankRepository->getAllBanks();
    int id = NONE;
    for (size_t i = 0; i < banks.size(); i++)
        if (banks[i].getID() == prod_el.getBankID())
            id = banks[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Product update error (bank not found)");
        throw ProductUpdateErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->repository->updateEl(prod_el);
    this->logger->log(INFO, "Update product success");
}

void ProductRules::deleteProduct(int id)
{
    Product tmpProduct = this->repository->getProductByID(id);
    if (tmpProduct.getID() > NONE)
    {
        try {
            this->repository->deleteEl(id);
            Product testProduct = this->repository->getProductByID(id);
            if (testProduct.getID() != NONE)
            {
                this->logger->log(ERROR, "Product delete error (can not delete)");
                throw ProductDeleteErrorException(__FILE__, typeid(*this).name(), __LINE__);
            }
            this->logger->log(INFO, "Delete product success");
        }
        catch (ProductNotFoundException) {}
    }
    else
    {
        this->logger->log(ERROR, "Product delete error (product not found)");
        throw ProductNotFoundException(__FILE__, typeid(*this).name(), __LINE__);
    }
}

int ProductRules::addProduct(ProductInfo inf)
{
    if ((inf.name.length() < 1) || (inf.min_time < MIN_TIME) || (inf.max_time < MIN_TIME)
        || (inf.min_time > inf.max_time) || (inf.min_sum < MIN_SUM)
        || (inf.max_sum < MIN_SUM) || (inf.min_sum > inf.max_sum) || (inf.count_rating < 0)
        || (inf.currency < ROUBLE) || (inf.currency > YUAN) || (inf.type < DEPOSIT)
        || (inf.type > CREDIT) || (inf.sum_rating < 0))
    {
        this->logger->log(ERROR, "Product add error (invalid params)");
        throw ProductAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::vector<Bank> banks = this->bankRepository->getAllBanks();
    int id = NONE;
    for (size_t i = 0; i < banks.size(); i++)
        if (banks[i].getID() == inf.bank_id)
            id = banks[i].getID();
    if (id == NONE)
    {
        this->logger->log(ERROR, "Product add error (bank not found)");
        throw ProductAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    id = this->repository->addProduct(inf);
    Product tmpProduct = this->repository->getProductByID(id);
    if (tmpProduct.getID() == NONE)
    {
        this->logger->log(ERROR, "Product add error (can not add)");
        throw ProductAddErrorException(__FILE__, typeid(*this).name(), __LINE__);
    }
    this->logger->log(INFO, "Add product success");
    return id;
}

std::vector<Product> ProductRules::getAllProducts()
{
    std::vector<Product> products = this->repository->getAllProducts();
    this->logger->log(INFO, "Get all products success");
    return products;
}
