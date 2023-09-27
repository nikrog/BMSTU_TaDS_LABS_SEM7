#include "PgRequestRepository.h"

Request PgRequestRepository::getRequestByID(int id)
{
    Request resultReq;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByID().get_str(id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            if (result.size() > 0)
            {
                if (result[0][7].is_null())
                {
                    resultReq = Request(id, result[0][1].as<int>(), result[0][2].as<int>(), NONE,
                                  result[0][3].as<float>(), result[0][4].as<int>(), result[0][5].as<timereq_t>(),
                                   State_t(result[0][6].as<int>()));
                }
                else
                {
                    resultReq = Request(id, result[0][1].as<int>(), result[0][2].as<int>(), result[0][7].as<int>(),
                                  result[0][3].as<float>(), result[0][4].as<int>(), result[0][5].as<timereq_t>(),
                                   State_t(result[0][6].as<int>()));
                }  
            }
            else
                resultReq = Request();
            curConnect.commit();
        }
        else
            throw DatabaseConnectException(__FILE__, typeid(*this).name(), __LINE__);
    }
    catch (const std::exception &e)
    {
          std::cout << e.what() << std::endl;
    }
    return resultReq;  
}

std::vector<Request> PgRequestRepository::getRequestByState(State_t state)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByState().get_str(state);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getRequestByDate(timereq_t date)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByDate().get_str(date);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getRequestByClient(int client_id)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByClient().get_str(client_id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getRequestByManager(int manager_id)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByManager().get_str(manager_id);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getRequestBySum(float min_sum, float max_sum)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestBySum().get_str(min_sum, max_sum);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getRequestByDuration(int min_time, int max_time)
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetRequestByDuration().get_str(min_time, max_time);
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

std::vector<Request> PgRequestRepository::getAllRequests()
{
    std::vector<Request> resultRequests = std::vector<Request>();
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLGetAllRequests().get_str();
            pqxx::work curConnect(*this->connection);
            pqxx::result result = curConnect.exec(sql);
            for (size_t i = 0; i < result.size(); i++)
            {
                Request currentReq;
                if (result[i][7].is_null())
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                    NONE, result[i][3].as<float>(), result[i][4].as<int>(),
                                     result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                else
                {
                    currentReq = Request(result[i][0].as<int>(), result[i][1].as<int>(), result[i][2].as<int>(),
                                        result[i][7].as<int>(), result[i][3].as<float>(), result[i][4].as<int>(),
                                        result[i][5].as<timereq_t>(), State_t(result[i][6].as<int>()));
                }
                resultRequests.push_back(currentReq);
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
    return resultRequests;
}

int PgRequestRepository::addRequest(RequestInfo inf)
{
    int res_id = -1;
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLAddRequest().get_str(inf);
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

void PgRequestRepository::deleteEl(int id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLDeleteRequest().get_str(id);
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

void PgRequestRepository::updateEl(Request req_el)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLUpdateRequest().get_str(req_el);
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

void PgRequestRepository::callRateProduct(int req_id, int score)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLCallRateProduct().get_str(req_id, score);
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

void PgRequestRepository::callMakeRequest(int cl_id, int prod_id, float sum, int dur)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLCallMakeRequest().get_str(cl_id, prod_id, sum, dur);
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

void PgRequestRepository::callConfirmRequest(int req_id, int manager_id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLCallConfirmRequest().get_str(req_id, manager_id);
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

void PgRequestRepository::callRejectRequest(int req_id, int manager_id)
{
    try
    {
        if (this->connection->is_open())
        {
            std::string sql = PostgreSQLCallRejectRequest().get_str(req_id, manager_id);
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
