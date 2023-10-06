#ifndef PPO_POSTGRESCOMMANDS_H
#define PPO_POSTGRESCOMMANDS_H

#include "../../business_logic/models/ModelUser.h"
#include "../../business_logic/models/ModelClient.h"
#include "../../business_logic/models/ModelBank.h"
#include "../../business_logic/models/ModelManager.h"
#include "../../business_logic/models/ModelProduct.h"
#include "../../business_logic/models/ModelRequest.h"

class PostgreSQLGetUserByID
{
public:
    PostgreSQLGetUserByID() = default;
    ~PostgreSQLGetUserByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetUserByLogin
{
public:
    PostgreSQLGetUserByLogin() = default;
    ~PostgreSQLGetUserByLogin() = default;
    std::string get_str(std::string login);
};

class PostgreSQLGetUserID
{
public:
    PostgreSQLGetUserID() = default;
    ~PostgreSQLGetUserID() = default;
    std::string get_str(std::string login);
};

class PostgreSQLAddUser
{
public:
    PostgreSQLAddUser() = default;
    ~PostgreSQLAddUser() = default;
    std::string get_str(UserInfo inf);
};

class PostgreSQLDeleteUser
{
public:
    PostgreSQLDeleteUser() = default;
    ~PostgreSQLDeleteUser() = default;
    std::string get_str(int id);
};

class PostgreSQLUpdateUser
{
public:
    PostgreSQLUpdateUser() = default;
    ~PostgreSQLUpdateUser() = default;
    std::string get_str(User user_el);
};

class PostgreSQLGetAllUsers
{
public:
    PostgreSQLGetAllUsers() = default;
    ~PostgreSQLGetAllUsers() = default;
    std::string get_str();
};

class PostgreSQLGetManagerByID
{
public:
    PostgreSQLGetManagerByID() = default;
    ~PostgreSQLGetManagerByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetManagerByUID
{
public:
    PostgreSQLGetManagerByUID() = default;
    ~PostgreSQLGetManagerByUID() = default;
    std::string get_str(int user_id);
};

class PostgreSQLGetManagerByBank
{
public:
    PostgreSQLGetManagerByBank() = default;
    ~PostgreSQLGetManagerByBank() = default;
    std::string get_str(int bank_id);
};

class PostgreSQLAddManager
{
public:
    PostgreSQLAddManager() = default;
    ~PostgreSQLAddManager() = default;
    std::string get_str(int user_id, int bank_id);
};

class PostgreSQLUpdateManager
{
public:
    PostgreSQLUpdateManager() = default;
    ~PostgreSQLUpdateManager() = default;
    std::string get_str(Manager manager_el);
};

class PostgreSQLDeleteManager
{
public:
    PostgreSQLDeleteManager() = default;
    ~PostgreSQLDeleteManager() = default;
    std::string get_str(int id);
};

class PostgreSQLGetAllManagers
{
public:
    PostgreSQLGetAllManagers() = default;
    ~PostgreSQLGetAllManagers() = default;
    std::string get_str();
};

class PostgreSQLGetBankByID
{
public:
    PostgreSQLGetBankByID() = default;
    ~PostgreSQLGetBankByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetBankByName
{
public:
    PostgreSQLGetBankByName() = default;
    ~PostgreSQLGetBankByName() = default;
    std::string get_str(std::string name);
};

class PostgreSQLAddBank
{
public:
    PostgreSQLAddBank() = default;
    ~PostgreSQLAddBank() = default;
    std::string get_str(BankInfo inf);
};

class PostgreSQLUpdateBank
{
public:
    PostgreSQLUpdateBank() = default;
    ~PostgreSQLUpdateBank() = default;
    std::string get_str(Bank bank_el);
};

class PostgreSQLDeleteBank
{
public:
    PostgreSQLDeleteBank() = default;
    ~PostgreSQLDeleteBank() = default;
    std::string get_str(int id);
};

class PostgreSQLGetAllBanks
{
public:
    PostgreSQLGetAllBanks() = default;
    ~PostgreSQLGetAllBanks() = default;
    std::string get_str();
};

class PostgreSQLGetProductByID
{
public:
    PostgreSQLGetProductByID() = default;
    ~PostgreSQLGetProductByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetProductByName
{
public:
    PostgreSQLGetProductByName() = default;
    ~PostgreSQLGetProductByName() = default;
    std::string get_str(std::string name);
};

class PostgreSQLGetProductByRate
{
public:
    PostgreSQLGetProductByRate() = default;
    ~PostgreSQLGetProductByRate() = default;
    std::string get_str(Prodtype type, float rate);
};


class PostgreSQLGetProductByBank
{
public:
    PostgreSQLGetProductByBank() = default;
    ~PostgreSQLGetProductByBank() = default;
    std::string get_str(Prodtype type, int bank_id);
};


class PostgreSQLGetProductBySum
{
public:
    PostgreSQLGetProductBySum() = default;
    ~PostgreSQLGetProductBySum() = default;
    std::string get_str(Prodtype type, float min_sum, float max_sum);
};

class PostgreSQLGetProductByTime
{
public:
    PostgreSQLGetProductByTime() = default;
    ~PostgreSQLGetProductByTime() = default;
    std::string get_str(Prodtype type, int min_time, int max_time);
};

class PostgreSQLGetProductByType
{
public:
    PostgreSQLGetProductByType() = default;
    ~PostgreSQLGetProductByType() = default;
    std::string get_str(Prodtype type);
};

class PostgreSQLGetProductByRating
{
public:
    PostgreSQLGetProductByRating() = default;
    ~PostgreSQLGetProductByRating() = default;
    std::string get_str(Prodtype type, float rating);
};

class PostgreSQLGetProductByCurrency
{
public:
    PostgreSQLGetProductByCurrency() = default;
    ~PostgreSQLGetProductByCurrency() = default;
    std::string get_str(Prodtype type, Curtype currency);
};

class PostgreSQLAddProduct
{
public:
    PostgreSQLAddProduct() = default;
    ~PostgreSQLAddProduct() = default;
    std::string get_str(ProductInfo inf);
};

class PostgreSQLUpdateProduct
{
public:
    PostgreSQLUpdateProduct() = default;
    ~PostgreSQLUpdateProduct() = default;
    std::string get_str(Product product_el);
};

class PostgreSQLDeleteProduct
{
public:
    PostgreSQLDeleteProduct() = default;
    ~PostgreSQLDeleteProduct() = default;
    std::string get_str(int id);
};

class PostgreSQLGetAllProducts
{
public:
    PostgreSQLGetAllProducts() = default;
    ~PostgreSQLGetAllProducts() = default;
    std::string get_str();
};

class PostgreSQLGetClientByID
{
public:
    PostgreSQLGetClientByID() = default;
    ~PostgreSQLGetClientByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetClientByFIO
{
public:
    PostgreSQLGetClientByFIO() = default;
    ~PostgreSQLGetClientByFIO() = default;
    std::string get_str(FIO name);
};

class PostgreSQLAddClient
{
public:
    PostgreSQLAddClient() = default;
    ~PostgreSQLAddClient() = default;
    std::string get_str(ClientInfo inf);
};

class PostgreSQLUpdateClient
{
public:
    PostgreSQLUpdateClient() = default;
    ~PostgreSQLUpdateClient() = default;
    std::string get_str(Client client_el);
};

class PostgreSQLDeleteClient
{
public:
    PostgreSQLDeleteClient() = default;
    ~PostgreSQLDeleteClient() = default;
    std::string get_str(int id);
};

class PostgreSQLGetAllClients
{
public:
    PostgreSQLGetAllClients() = default;
    ~PostgreSQLGetAllClients() = default;
    std::string get_str();
};

class PostgreSQLGetRequestByID
{
public:
    PostgreSQLGetRequestByID() = default;
    ~PostgreSQLGetRequestByID() = default;
    std::string get_str(int id);
};

class PostgreSQLGetRequestByState
{
public:
    PostgreSQLGetRequestByState() = default;
    ~PostgreSQLGetRequestByState() = default;
    std::string get_str(State_t state);
};

class PostgreSQLGetRequestByDate
{
public:
    PostgreSQLGetRequestByDate() = default;
    ~PostgreSQLGetRequestByDate() = default;
    std::string get_str(timereq_t date);
};

class PostgreSQLGetRequestByClient
{
public:
    PostgreSQLGetRequestByClient() = default;
    ~PostgreSQLGetRequestByClient() = default;
    std::string get_str(int client_id);
};

class PostgreSQLGetRequestByManager
{
public:
    PostgreSQLGetRequestByManager() = default;
    ~PostgreSQLGetRequestByManager() = default;
    std::string get_str(int manager_id);
};

class PostgreSQLGetRequestBySum
{
public:
    PostgreSQLGetRequestBySum() = default;
    ~PostgreSQLGetRequestBySum() = default;
    std::string get_str(float min_sum, float max_sum);
};

class PostgreSQLGetRequestByDuration
{
public:
    PostgreSQLGetRequestByDuration() = default;
    ~PostgreSQLGetRequestByDuration() = default;
    std::string get_str(int min_time, int max_time);
};

class PostgreSQLAddRequest
{
public:
    PostgreSQLAddRequest() = default;
    ~PostgreSQLAddRequest() = default;
    std::string get_str(RequestInfo inf);
};

class PostgreSQLUpdateRequest
{
public:
    PostgreSQLUpdateRequest() = default;
    ~PostgreSQLUpdateRequest() = default;
    std::string get_str(Request request_el);
};

class PostgreSQLDeleteRequest
{
public:
    PostgreSQLDeleteRequest() = default;
    ~PostgreSQLDeleteRequest() = default;
    std::string get_str(int id);
};

class PostgreSQLGetAllRequests
{
public:
    PostgreSQLGetAllRequests() = default;
    ~PostgreSQLGetAllRequests() = default;
    std::string get_str();
};

class PostgreSQLFilterProducts
{
public:
    PostgreSQLFilterProducts() = default;
    ~PostgreSQLFilterProducts() = default;
    std::string get_str(ProductFilter f);
};

class PostgreSQLSetRole
{
public:
    PostgreSQLSetRole() = default;
    ~PostgreSQLSetRole() = default;
    std::string get_str(Roles role);
};

class PostgreSQLCallRateProduct
{
public:
    PostgreSQLCallRateProduct() = default;
    ~PostgreSQLCallRateProduct() = default;
    std::string get_str(int prod_id, int score);
};

class PostgreSQLCallMakeRequest
{
public:
    PostgreSQLCallMakeRequest() = default;
    ~PostgreSQLCallMakeRequest() = default;
    std::string get_str(int cl_id, int prod_id, float sum, int dur);
};

class PostgreSQLCallConfirmRequest
{
public:
    PostgreSQLCallConfirmRequest() = default;
    ~PostgreSQLCallConfirmRequest() = default;
    std::string get_str(int req_id, int manager_id);
};

class PostgreSQLCallRejectRequest
{
public:
    PostgreSQLCallRejectRequest() = default;
    ~PostgreSQLCallRejectRequest() = default;
    std::string get_str(int req_id, int manager_id);
};
#endif //PPO_POSTGRESCOMMANDS_H
