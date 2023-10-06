#include "ProductPrinter.h"

void ProductPrinter::printProduct(Product prod_el)
{
    std::cout << prod_el.getID() << " " << prod_el.getName();

    if (prod_el.getType() == 0)
        std::cout << " тип: депозит";
    
    else if (prod_el.getType() == 1)
        std::cout << " тип: кредит";
    
    std::cout << ", bank_id - " \
                 << prod_el.getBankID() << ", ставка: " << prod_el.getRate() <<  ", мин. срок: " \
                 << prod_el.getMinTime() << ",  макс. срок: " << prod_el.getMaxTime() \
                 << ", мин. сумма: " << prod_el.getMinSum() << ", макс. сумма: " << prod_el.getMaxSum() \
                 << ", рейтинг: " << prod_el.getAvgRating();
    
    if (prod_el.getCurrency() == 0)
        std::cout << ", валюта: Рубль";
    
    else if (prod_el.getCurrency() == 1)
        std::cout << ", валюта: Доллар";

    else if (prod_el.getCurrency() == 2)
        std::cout << ", валюта: Евро";
    
    else if (prod_el.getCurrency() == 3)
        std::cout << ", валюта: Юань";

    std::cout << std::endl;
}

void ProductPrinter::printInputID()
{
    std::cout << PRODUCT_ID_INPUT_MESSAGE;
}

void ProductPrinter::printInputBankID()
{
    std::cout << BANK_ID_INPUT_MESSAGE;
}

void ProductPrinter::printInputType()
{
    std::cout << PROD_TYPE_INPUT_MESSAGE;
}

void ProductPrinter::printInputName()
{
    std::cout << PROD_NAME_INPUT_MESSAGE;
}

void ProductPrinter::printInputRate()
{
    std::cout << RATE_INPUT_MESSAGE;
}

void ProductPrinter::printInputMinTime()
{
    std::cout << MIN_TIME_INPUT_MESSAGE;
}

void ProductPrinter::printInputMaxTime()
{
    std::cout << MAX_TIME_INPUT_MESSAGE;
}

void ProductPrinter::printInputMinSum()
{
    std::cout << MIN_SUM_INPUT_MESSAGE;
}

void ProductPrinter::printInputMaxSum()
{
    std::cout << MAX_SUM_INPUT_MESSAGE;
}

void ProductPrinter::printInputCurrency()
{
    std::cout << CURRENCY_INPUT_MESSAGE;
}

void ProductPrinter::printInputScore()
{
    std::cout << SCORE_INPUT_MESSAGE;
}

void ProductPrinter::printAddSuccess()
{
    std::cout << ADD_SUCCESS;
}

void ProductPrinter::printException(const std::exception &e)
{
    std::cout << e.what() << std::endl;
}
