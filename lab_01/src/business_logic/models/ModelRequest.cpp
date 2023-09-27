#include "ModelRequest.h"

Request::Request(int id, int client_id, int product_id, int manager_id, float sum,
                 int duration, timereq_t date, State_t state)
{
    this->id = id;
    this->client_id = client_id;
    this->product_id = product_id;
    this->manager_id = manager_id;
    this->sum = sum;
    this->duration = duration;
    this->date = date;
    this->state = state;
}
Request::Request()
{
    this->id = NONE;
    this->client_id = NONE;
    this->product_id = NONE;
    this->manager_id = NONE;
    this->sum = 0;
    this->duration = 0;
    this->date = DEF_TIME2;
    this->state = OPENED;
}

Request::~Request()
{}

int Request::getID()
{
    return this->id;
}

int Request::getClientID()
{
    return this->client_id;
}
int Request::getProductID()
{
    return this->product_id;
}
int Request::getManagerID()
{
    return this->manager_id;
}
float Request::getSum()
{
    return this->sum;
}
int Request::getDuration()
{
    return this->duration;
}
timereq_t Request::getDate()
{
    return this->date;
}
State_t Request::getState()
{
    return this->state;
}


void Request::setSum(float sum)
{
    this->sum = sum;
}
void Request::setDuration(int duration)
{
    this->duration = duration;
}
void Request::setDate(date_t date)
{
    this->date = date;
}
void Request::setState(State_t state)
{
    this->state = state;
}
void Request::setManagerID(int manager_id)
{
    this->manager_id = manager_id;
}
