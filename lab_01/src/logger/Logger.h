#ifndef PPO_LOGGER_H
#define PPO_LOGGER_H


#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "../business_logic/models/constants.h"
#include "../business_logic/rules/ILogger.h"


class Logger : public ILogger{
private:
    std::string log_file;
    LogLevel log_level;
public:
    Logger(std::string log_f, LogLevel lvl) : ILogger(), log_file(log_f), log_level(lvl) {

    }
    ~Logger();
    void log(LogLevel lvl, std::string log_str) override;
    std::string get_str_lvl(LogLevel lvl) override;
};


#endif //PPO_LOGGER_H
