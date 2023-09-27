#include "Logger.h"


Logger::~Logger()
{}

std::string Logger::get_str_lvl(LogLevel lvl)
{
    std::string res;
    switch (lvl)
    {
        case DEBUG:
            res = "DEBUG";
            break;
        
        case INFO:
            res = "INFO";
            break;
        
        case WARNING:
            res = "WARNING";
            break;
        
        case ERROR:
            res = "ERROR";
            break;
        
        case FATAL:
            res = "FATAL";
            break;

        default:
            res = "UNKNOWN";
    }
    return res;
}

void Logger::log(LogLevel lvl, std::string log_str)
{
    if (lvl >= this->log_level)
    {
        std::ofstream out(this->log_file, std::fstream::app);
        if (out.is_open())
        {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            out << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " : " << get_str_lvl(lvl) << " : " << log_str << std::endl;
        }
    }
}
