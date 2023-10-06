#ifndef PPO_REQUESTPRINTER_H
#define PPO_REQUESTPRINTER_H

#include <iostream>
#include <string>
#include "../../business_logic/models/ModelRequest.h"
#include "../../business_logic/models/constants.h"

class RequestPrinter {
public:
    RequestPrinter() = default;
    ~RequestPrinter() = default;
    void printRequest(Request req_el);
    void printInputID();
    void printInputClientID();
    void printInputProductID();
    void printInputManagerID();
    void printInputSum();
    void printInputDuration();
    void printInputDate();
    void printInputState();
    void printInputScore();
    void printAddSuccess();
    void printException(const std::exception &e);
};


#endif //PPO_REQUESTPRINTER_H
