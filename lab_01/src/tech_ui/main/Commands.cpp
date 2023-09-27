#include "Commands.h"

bool CommandHandler::check_is_number(std::string cmd)
{
    return !cmd.empty() && std::all_of(cmd.begin(), cmd.end(), ::isdigit);
}

CMD_KEYS CommandHandler::handle(std::string cmd)
{
    CMD_KEYS res = NOT_A_COMMAND;
    if (cmd.size() < 3 && check_is_number(cmd))
    {
        int num = std::stoi(cmd);
        if (num < NOT_A_COMMAND)
        {
            res = (CMD_KEYS) num;
        }
    }
    return res;
}