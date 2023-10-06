#include "PostgresCommands.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string PostgreSQLGetUserByID::get_str(int id)
{
    return "SELECT * FROM BA.users WHERE user_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetUserByLogin::get_str(std::string login)
{
    return "SELECT * FROM BA.users WHERE login = '" + login + "';";
}

std::string PostgreSQLGetUserID::get_str(std::string login)
{
    return "SELECT user_id FROM BA.users WHERE login = '" + login + "';";
}

std::string PostgreSQLAddUser::get_str(UserInfo inf)
{
    return "INSERT INTO BA.users(login, password, permission) VALUES ('" + inf.login + "', '" + inf.password + "', " +
    std::to_string(inf.permission) + ") RETURNING user_id;";
}

std::string PostgreSQLDeleteUser::get_str(int id)
{
    return "DELETE FROM BA.users WHERE user_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateUser::get_str(User user_el)
{
    return "UPDATE BA.users SET login = '" + user_el.getLogin() + "', password = '" + user_el.getPassword() + "', permission = " +
    std::to_string(user_el.getUserRole()) + "WHERE user_id = " + std::to_string(user_el.getID()) + ";";
}

std::string PostgreSQLGetAllUsers::get_str()
{
    return "SELECT * FROM BA.users ORDER BY user_id";
}

std::string PostgreSQLGetManagerByID::get_str(int id)
{
    return "SELECT * FROM BA.managers WHERE manager_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetManagerByUID::get_str(int user_id)
{
    return "SELECT * FROM BA.managers WHERE user_id = " + std::to_string(user_id) + ";";
}

std::string PostgreSQLGetManagerByBank::get_str(int bank_id)
{
    return "SELECT * FROM BA.managers WHERE bank_id = " + std::to_string(bank_id) + ";";
}

std::string PostgreSQLAddManager::get_str(int user_id, int bank_id)
{
    return "INSERT INTO BA.managers(user_id, bank_id) VALUES (" + std::to_string(user_id) + ", " + std::to_string(bank_id) 
    + ") RETURNING manager_id;";
}

std::string PostgreSQLDeleteManager::get_str(int id)
{
    return "DELETE FROM BA.managers WHERE manager_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateManager::get_str(Manager manager_el)
{
    return "UPDATE BA.managers SET user_id = " + std::to_string(manager_el.getUserID()) + ", bank_id = " + std::to_string(manager_el.getBankID()) 
    + "WHERE manager_id = " + std::to_string(manager_el.getID()) + ";";
}

std::string PostgreSQLGetAllManagers::get_str()
{
    return "SELECT * FROM BA.managers ORDER BY manager_id;";
}

std::string PostgreSQLGetBankByID::get_str(int id)
{
    return "SELECT * FROM BA.banks WHERE bank_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetBankByName::get_str(std::string name)
{
    return "SELECT * FROM BA.banks WHERE name = '" + name + "';";
}

std::string PostgreSQLAddBank::get_str(BankInfo inf)
{
    return "INSERT INTO BA.banks(name, license_num, address, email, phone, website) VALUES ('" + inf.name + "', "
    + std::to_string(inf.license_num) + ", '" + inf.address + "', '" + inf.email + "', '" + inf.phone + "', '" + inf.website 
    + "') RETURNING bank_id;";
}

std::string PostgreSQLDeleteBank::get_str(int id)
{
    return "DELETE FROM BA.banks WHERE bank_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateBank::get_str(Bank bank_el)
{
    return "UPDATE BA.banks SET name = '" + bank_el.getName() + "', license_num = " + std::to_string(bank_el.getLicenseNum())
    + ", address = '" + bank_el.getAddress() + "', email = '" + bank_el.getEmail() + "', phone = '" + bank_el.getPhone() + "', website = '"
    + bank_el.getWebsite() + "' WHERE bank_id = " + std::to_string(bank_el.getID()) + ";";
}

std::string PostgreSQLGetAllBanks::get_str()
{
    return "SELECT * FROM BA.banks ORDER BY bank_id";
}

std::string PostgreSQLGetProductByID::get_str(int id)
{
    return "SELECT * FROM BA.products WHERE product_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetProductByName::get_str(std::string name)
{
    return "SELECT * FROM BA.products WHERE name = '" + name + "';";
}

std::string PostgreSQLGetProductByRate::get_str(Prodtype type, float rate)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND rate >= " + std::to_string(rate) + ";";
}

std::string PostgreSQLGetProductByBank::get_str(Prodtype type, int bank_id)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND bank_id = " + std::to_string(bank_id) + ";";
}

std::string PostgreSQLGetProductBySum::get_str(Prodtype type, float min_sum, float max_sum)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND min_sum <= " + std::to_string(min_sum)
    + "AND max_sum >= " + std::to_string(max_sum) + ";";
}

std::string PostgreSQLGetProductByTime::get_str(Prodtype type, int min_time, int max_time)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND min_time <= " + std::to_string(min_time)
    + "AND max_time >= " + std::to_string(max_time) + ";";
}

std::string PostgreSQLGetProductByType::get_str(Prodtype type)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + ";";
}

std::string PostgreSQLGetProductByRating::get_str(Prodtype type, float rating)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND BA.calc_rating(product_id) >= "
     + std::to_string(rating) + ";";
}

std::string PostgreSQLGetProductByCurrency::get_str(Prodtype type, Curtype currency)
{
    return "SELECT * FROM BA.products WHERE ptype = " + std::to_string(type) + "AND currency = "
     + std::to_string(currency) + ";";
}

std::string PostgreSQLAddProduct::get_str(ProductInfo inf)
{
    std::string rate = std::to_string(inf.rate);
    std::replace(rate.begin(), rate.end(), ',', '.' );
    std::string min_sum = std::to_string(inf.min_sum);
    std::replace(min_sum.begin(), min_sum.end(), ',', '.' );
    std::string max_sum = std::to_string(inf.max_sum);
    std::replace(max_sum.begin(), max_sum.end(), ',', '.' );
    return "INSERT INTO BA.products(ptype, name, bank_id, rate, min_time, max_time, min_sum, max_sum, currency, sum_rating, count_rating) VALUES (" + std::to_string(inf.type) + ", '" + inf.name + "', "
    + std::to_string(inf.bank_id) + ", " + rate + ", " + std::to_string(inf.min_time) + ", "
    + std::to_string(inf.max_time) + ", " + min_sum + ", " + max_sum + ", "
    + std::to_string(inf.currency) + ", " + std::to_string(inf.sum_rating) + ", " + std::to_string(inf.count_rating) 
    + ") RETURNING product_id;";
}

std::string PostgreSQLDeleteProduct::get_str(int id)
{
    return "DELETE FROM BA.products WHERE product_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateProduct::get_str(Product prod_el)
{
    std::string min_sum = std::to_string(prod_el.getMinSum());
    std::replace(min_sum.begin(), min_sum.end(), ',', '.' );
    std::string max_sum = std::to_string(prod_el.getMaxSum());
    std::replace(max_sum.begin(), max_sum.end(), ',', '.' );
    std::string rate = std::to_string(prod_el.getRate());
    std::replace(rate.begin(), rate.end(), ',', '.' );
    return "UPDATE BA.products SET ptype = " + std::to_string(prod_el.getType()) + ", name = '" + prod_el.getName()
    + "', bank_id = " + std::to_string(prod_el.getBankID()) + ", rate = " + rate
    + ", min_time = " + std::to_string(prod_el.getMinTime()) + ", max_time = "
    + std::to_string(prod_el.getMaxTime()) + ", min_sum = " + min_sum + ", max_sum = "
    + max_sum + ", currency = " + std::to_string(prod_el.getCurrency()) + ", sum_rating = "
    + std::to_string(prod_el.getSumRating()) + ", count_rating = " + std::to_string(prod_el.getCountRating())
    + "WHERE product_id = " + std::to_string(prod_el.getID()) + ";";
}

std::string PostgreSQLGetAllProducts::get_str()
{
    return "SELECT * FROM BA.products";
}

std::string PostgreSQLGetClientByID::get_str(int id)
{
    return "SELECT * FROM BA.clients WHERE client_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetClientByFIO::get_str(FIO name)
{
    return "SELECT * FROM BA.clients WHERE name = '" + name.name + "' AND surname = '" + name.surname + "' AND patronymic = '" 
    + name.patronymic + "';";
}

std::string PostgreSQLAddClient::get_str(ClientInfo inf)
{
    return "INSERT INTO BA.clients(name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES ('" 
    + inf.name + "', '" + inf.surname + "', '" + inf.patronymic + "', " + std::to_string(inf.passport_num) 
    + ", " + std::to_string(inf.birth_date) + ", '" + inf.address + "', '" + inf.email + "', '" + inf.phone + "', "
    + std::to_string(inf.user_id) + ") RETURNING client_id;";
}

std::string PostgreSQLDeleteClient::get_str(int id)
{
    return "DELETE FROM BA.clients WHERE client_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateClient::get_str(Client client_el)
{
    return "UPDATE BA.clients SET name = '" + client_el.getName() + "', surname = '" + client_el.getSurname()
    + "', patronymic = '" + client_el.getPatronymic() + "', passport_num = " + std::to_string(client_el.getPassportNum()) 
    + ", birth_date = " + std::to_string(client_el.getBirthDate()) + ", address = '"
    + client_el.getAddress() + "', email = '" + client_el.getEmail() + "', phone = '"
    + client_el.getPhone() + "', user_id = " + std::to_string(client_el.getUserID())
    + "WHERE client_id = " + std::to_string(client_el.getID()) + ";";
}

std::string PostgreSQLGetAllClients::get_str()
{
    return "SELECT * FROM BA.clients ORDER by client_id;";
}

std::string PostgreSQLGetRequestByID::get_str(int id)
{
    return "SELECT * FROM BA.requests WHERE request_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLGetRequestByState::get_str(State_t state)
{
    return "SELECT * FROM BA.requests WHERE state = " + std::to_string(state) + ";";
}

std::string PostgreSQLGetRequestByDate::get_str(timereq_t date)
{
    return "SELECT * FROM BA.requests WHERE date >= '" + date + "';";
}

std::string PostgreSQLGetRequestByClient::get_str(int client_id)
{
    return "SELECT * FROM BA.requests WHERE client_id = " + std::to_string(client_id) + "ORDER by request_id;";
}

std::string PostgreSQLGetRequestByManager::get_str(int manager_id)
{
    if (manager_id == NONE)
    {
        return "SELECT * FROM BA.requests WHERE manager_id is null;";
    }
    else
        return "SELECT * FROM BA.requests WHERE manager_id = " + std::to_string(manager_id) + ";";
}

std::string PostgreSQLGetRequestBySum::get_str(float min_sum, float max_sum)
{
    return "SELECT * FROM BA.requests WHERE sum >= " + std::to_string(min_sum) 
    + " AND sum <= " + std::to_string(max_sum) + ";";
}

std::string PostgreSQLGetRequestByDuration::get_str(int min_time, int max_time)
{
    return "SELECT * FROM BA.requests WHERE duration >= " + std::to_string(min_time) 
    + " AND duration <= " + std::to_string(max_time) + ";";
}

std::string PostgreSQLAddRequest::get_str(RequestInfo inf)
{
    std::string sum = std::to_string(inf.sum);
    std::replace(sum.begin(), sum.end(), ',', '.' );
    if (inf.manager_id == NONE)
    {
        return "INSERT INTO BA.requests (client_id, product_id, sum, duration, date, state, manager_id)  VALUES (" 
        + std::to_string(inf.client_id) + ", " + std::to_string(inf.product_id) + ", " + sum + ", " + std::to_string(inf.duration)
        + ", '" + inf.date + "', " + std::to_string(inf.state) + ", null) RETURNING request_id;";
    }
    else
    {
        return "INSERT INTO BA.requests (client_id, product_id, sum, duration, date, state, manager_id)  VALUES (" 
        + std::to_string(inf.client_id) + ", " + std::to_string(inf.product_id) + ", " + sum + ", " + std::to_string(inf.duration)
        + ", '" + inf.date + "', " + std::to_string(inf.state) + ", " + std::to_string(inf.manager_id)
        + ") RETURNING request_id;";
    }
}

std::string PostgreSQLDeleteRequest::get_str(int id)
{
    return "DELETE FROM BA.requests WHERE request_id = " + std::to_string(id) + ";";
}

std::string PostgreSQLUpdateRequest::get_str(Request request_el)
{
    std::string sum = std::to_string(request_el.getSum());
    std::replace(sum.begin(), sum.end(), ',', '.' );
    if (request_el.getManagerID() == NONE)
    {
        return "UPDATE BA.requests SET client_id = " + std::to_string(request_el.getClientID()) + ", product_id = " 
        + std::to_string(request_el.getProductID())
        + ", sum = " + sum + ", duration = " + std::to_string(request_el.getDuration())
        + ", date = '" + request_el.getDate() + "', state = "
        + std::to_string(request_el.getState()) + ", manager_id = null "
        + "WHERE request_id = " + std::to_string(request_el.getID()) + ";";
    }
    else
    {
        return "UPDATE BA.requests SET client_id = " + std::to_string(request_el.getClientID()) + ", product_id = " 
        + std::to_string(request_el.getProductID())
        + ", sum = " + sum + ", duration = " + std::to_string(request_el.getDuration())
        + ", date = '" + request_el.getDate() + "', state = "
        + std::to_string(request_el.getState()) + ", manager_id = " + std::to_string(request_el.getManagerID())
        + " WHERE request_id = " + std::to_string(request_el.getID()) + ";";
    }
}

std::string PostgreSQLGetAllRequests::get_str()
{
    return "SELECT * FROM BA.requests ORDER by request_id;";
}

std::string PostgreSQLFilterProducts::get_str(ProductFilter f)
{
    std::string s_filter = "SELECT * FROM BA.products WHERE ptype = " + std::to_string(f.type);
    if (f.bank_id != NONE)
    {
        s_filter += " AND bank_id = " + std::to_string(f.bank_id);
    }
    if (!f.name.empty())
    {
        s_filter += " AND name = '" + f.name + "'";
    }
    if (f.min_sum > 0)
    {
        s_filter += " AND min_sum >= " + std::to_string(f.min_sum);
    }
    if (f.max_sum > 0)
    {
        s_filter += " AND max_sum <= " + std::to_string(f.max_sum);
    }
    if (f.min_time > 0)
    {
        s_filter += " AND min_time >= " + std::to_string(f.min_time);
    }
    if (f.max_time > 0)
    {
        s_filter += " AND max_time <= " + std::to_string(f.max_time);
    }
    if (f.min_rate > -100)
    {
        s_filter += " AND rate >= " + std::to_string(f.min_rate);
    }
    if (f.max_rate > -100)
    {
        s_filter += " AND rate <= " + std::to_string(f.max_rate);
    }
    if (f.avg_rating > 0)
    {
        s_filter += " AND BA.calc_rating(product_id) >= " + std::to_string(f.avg_rating);
    }
    s_filter += "AND currency = " + std::to_string(f.currency);
    s_filter += " ORDER BY " + f.sort_param + " " + f.sort_dir +";";
    std::replace(s_filter.begin(), s_filter.end(), ',', '.' );
    //std::cout << s_filter;
    return s_filter;
}

std::string PostgreSQLSetRole::get_str(Roles role)
{
    std::vector<std::string> roles_arr = {"Unauthorized", "Client", "Manager", "Administrator"};
    return "SET ROLE " + roles_arr[role] + ";";
}

std::string PostgreSQLCallRateProduct::get_str(int prod_id, int score)
{
    return "CALL BA.rate_product(" + std::to_string(prod_id) + ", " + std::to_string(score) + ");";
}

std::string PostgreSQLCallMakeRequest::get_str(int cl_id, int prod_id, float sum, int dur)
{
    std::string s_sum = std::to_string(sum);
    std::replace(s_sum.begin(), s_sum.end(), ',', '.' );
    return "CALL BA.make_request(" + std::to_string(cl_id) + ", " + std::to_string(prod_id) + ", "
            + s_sum + ", " + std::to_string(dur) + ");";
}

std::string PostgreSQLCallConfirmRequest::get_str(int req_id, int manager_id)
{
    return "CALL BA.confirm_request(" + std::to_string(req_id) + ", " + std::to_string(manager_id) + ");";
}

std::string PostgreSQLCallRejectRequest::get_str(int req_id, int manager_id)
{
    return "CALL BA.reject_request(" + std::to_string(req_id) + ", " + std::to_string(manager_id) + ");";
}
