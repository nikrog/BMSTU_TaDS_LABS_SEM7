#include "RequestPrinter.h"

void RequestPrinter::printRequest(Request req_el)
{
    std::cout << req_el.getID() << ", ID клиента - " << req_el.getClientID() << ", ID продукта - " \
    << req_el.getProductID();

    if (req_el.getManagerID() == NONE)
        std::cout << ", ID менеджера - не назначен";
    else
        std::cout << ", ID менеджера - " << req_el.getManagerID();
    
    std::cout << ", сумма - " << req_el.getSum() << ", срок - " << req_el.getDuration() << ", дата - " << req_el.getDate();

    if (req_el.getState() == 0)
        std::cout << ", статус - открыта";
    else if (req_el.getState() == 1)
        std::cout << ", статус - одобрена и не оценена";
    else if (req_el.getState() == 2)
        std::cout << ", статус - отклонена";
    else if (req_el.getState() == 3)
        std::cout << ", статус - одобрена и оценена";
    else if (req_el.getState() == 4)
        std::cout << ", статус - закрыта и оценена";
    else if (req_el.getState() == 5)
        std::cout << ", статус - закрыта и не оценена";
    
    std::cout << std::endl;
}   

void RequestPrinter::printInputID()
{
    std::cout << REQUEST_ID_INPUT_MESSAGE;
}
void RequestPrinter::printInputClientID()
{
    std::cout << CLIENT_ID_INPUT_MESSAGE;
}
void RequestPrinter::printInputProductID()
{
    std::cout << PRODUCT_ID_INPUT_MESSAGE;
}
void RequestPrinter::printInputManagerID()
{
    std::cout << MANAGER_ID_INPUT_MESSAGE;
}
void RequestPrinter::printInputSum()
{
    std::cout << SUM_INPUT_MESSAGE;
}
void RequestPrinter::printInputDuration()
{
    std::cout << DURATION_INPUT_MESSAGE;
}
void RequestPrinter::printInputDate()
{
    std::cout << DATE_INPUT_MESSAGE;
}
void RequestPrinter::printInputState()
{
    std::cout << STATE_INPUT_MESSAGE;
}
void RequestPrinter::printInputScore()
{
    std::cout << SCORE_INPUT_MESSAGE;
}
void RequestPrinter::printAddSuccess()
{
    std::cout << ADD_SUCCESS;
}
void RequestPrinter::printException(const std::exception &e)
{
    std::cout << e.what() << std::endl;
}