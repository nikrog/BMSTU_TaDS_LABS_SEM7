#ifndef PPO_CONFIGMANAGER_H
#define PPO_CONFIGMANAGER_H

#include <iostream>
#include <fstream>
#include "../data_access/connection/connection.h"
#include "../business_logic/models/constants.h"
#include "../business_logic/rules/ILogger.h"

//#define CONF_FILE "./config.txt"
#define CONF_FILE "/home/pavela/arper/PPO/ppo/src/config.txt"

class ConfigManager {
public:
    ConfigManager() = default;
    ~ConfigManager() = default;
    std::string getDB();
    ConnectionParams getParams();
    std::vector<int> getBLparams();
    LogLevel getLogLevel();
    std::string getLogFile();
};


#endif //PPO_CONFIGMANAGER_H
