#include "ManagerPrinter.h"

void ManagerPrinter::printManager(Manager tmpManager)
{
    std::cout << "ID менеджера: " << tmpManager.getID() << ", User ID: " << tmpManager.getUserID() 
    << ", ID банка: " << tmpManager.getBankID() << std::endl;
}

void ManagerPrinter::printInputID()
{
    std::cout << MANAGER_ID_INPUT_MESSAGE;
}

void ManagerPrinter::printInputBankID()
{
    std::cout << BANK_ID_INPUT_MESSAGE;
}

void ManagerPrinter::printInputUserID()
{
    std::cout << USER_ID_INPUT_MESSAGE;
}

void ManagerPrinter::printInputLogin()
{
    std::cout << LOGIN_INPUT_MESSAGE;
}

void ManagerPrinter::printInputPassword()
{
    std::cout << PASSWORD_INPUT_MESSAGE;
}

void ManagerPrinter::printChangeInfoSuccess()
{
    std::cout << CHANGE_SUCCESS;
}

void ManagerPrinter::printAddSuccess()
{
    std::cout << ADD_SUCCESS;
}

void ManagerPrinter::printException(const std::exception &e)
{
    std::cout << e.what() << std::endl;
}
