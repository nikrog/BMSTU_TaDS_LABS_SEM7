#ifndef PPO_ILOGGER_H
#define PPO_ILOGGER_H

#include <iostream>
#include <string>

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    FATAL = 4
};

#define LOG_FILE "app.log"

class ILogger {
public:
   virtual void log(LogLevel lvl, std::string log_str) = 0;
   virtual std::string get_str_lvl(LogLevel lvl) = 0;
};

#endif //PPO_ILOGGER_H