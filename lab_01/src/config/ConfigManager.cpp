#include "ConfigManager.h"

std::string ConfigManager::getDB()
{
    std::string s, result = "unknown";
    std::ifstream out(CONF_FILE, std::fstream::in);
    if (out.is_open())
    {
        out >> s >> s >> result;
    }
    return result;
}

ConnectionParams ConfigManager::getParams()
{
    std::ifstream out(CONF_FILE, std::fstream::in);
    if (out.is_open())
    {
        std::string s, user, host, dbname, password, port;
        out >> s >> s >> s;
        out >> s >> s >> user;
        out >> s >> s >> host;
        out >> s >> s >> dbname;
        out >> s >> s >> password;
        out >> s >> s >> port;
        
        return ConnectionParams(user, host, dbname, password, std::atoi(port.c_str()));
    }
    else
        return ConnectionParams();
}

std::vector<int> ConfigManager::getBLparams()
{
    std::vector<int> params;
    std::ifstream out(CONF_FILE, std::fstream::in);
    if (out.is_open())
    {
        std::string s, len_passw, len_login;
        int n;
        out >> s >> s >> s;
        out >> s >> s >> s;
        out >> s >> s >> s;
        out >> s >> s >> s;
        out >> s >> s >> s;
        out >> s >> s >> s;
        out >> s >> s >> len_login;
        out >> s >> s >> len_passw;
        n = std::stoi(len_passw);
        params.push_back(n);
        n = std::stoi(len_login);
        params.push_back(n);
    }
    return params;
}

LogLevel ConfigManager::getLogLevel()
{
    LogLevel lvl = INFO;
    std::ifstream out(CONF_FILE, std::fstream::in);
    if (out.is_open())
    {
        std::string s, s2, log_lvl;
        int n;
        for (int i=0; i < 8; i++)
        {
            out >> s >> s >> s;
        }
        
        out >> s >> s2 >> log_lvl;
        if (s == "LogLevel")
        {
            n = std::stoi(log_lvl);
            if (n <= FATAL)
                lvl = (LogLevel) n;
        }
    }
    return lvl;
}

std::string ConfigManager::getLogFile()
{
    std::string s, s2, s3, result = "file.log";
    std::ifstream out(CONF_FILE, std::fstream::in);
    if (out.is_open())
    {
        for (int i=0; i < 9; i++)
        {
            out >> s >> s >> s;
        }
        out >> s >> s2 >> s3;
        if (s == "LogFile")
        {
           result = s3;
        }
    }
    return result;
}
