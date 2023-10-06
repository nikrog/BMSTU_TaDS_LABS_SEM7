#include "ClientPrinter.h"

void ClientPrinter::printClient(Client tmpClient)
{
    std::cout << "Клиент: " << tmpClient.getSurname() << " " << tmpClient.getName() \
              << " " << tmpClient.getPatronymic() << " , номер паспорта - " << tmpClient.getPassportNum() \
              << " , дата рождения - " << tmpClient.getBirthDate() << " , адрес проживания - " \
              << tmpClient.getAddress() << " , email - " << tmpClient.getEmail() << " , номер телефона - " \
              << tmpClient.getPhone() << " , User ID - " << tmpClient.getUserID() << std::endl;
}


void ClientPrinter::printAllClients(std::vector<Client> clients)
{
    for (size_t i = 0; i < clients.size(); i++)
        printClient(clients[i]);
}

void ClientPrinter::printInputID()
{
    std::cout << CLIENT_ID_INPUT_MESSAGE;
}

void ClientPrinter::printInputName()
{
    std::cout << NAME_INPUT_MESSAGE;
}

void ClientPrinter::printInputSurname()
{
    std::cout << SURNAME_INPUT_MESSAGE;
}

void ClientPrinter::printInputPatronymic()
{
    std::cout << PATRONYMIC_INPUT_MESSAGE;
}

void ClientPrinter::printInputPassportNum()
{
    std::cout << PASSPORTNUM_INPUT_MESSAGE;
}

void ClientPrinter::printInputEmail()
{
    std::cout << EMAIL_INPUT_MESSAGE;
}

void ClientPrinter::printInputBirthDate()
{
    std::cout << BIRTHDATE_INPUT_MESSAGE;
}

void ClientPrinter::printInputAddress()
{
    std::cout << ADDRESS_INPUT_MESSAGE;
}

void ClientPrinter::printInputPhone()
{
    std::cout << PHONE_INPUT_MESSAGE;
}

void ClientPrinter::printInputLogin()
{
    std::cout << LOGIN_INPUT_MESSAGE;
}

void ClientPrinter::printInputPassword()
{
    std::cout << PASSWORD_INPUT_MESSAGE;
}

void ClientPrinter::printChangeInfoSuccess()
{
    std::cout << CHANGE_SUCCESS;
}

void ClientPrinter::printException(const std::exception &e)
{
    std::cout << e.what() << std::endl;
}
