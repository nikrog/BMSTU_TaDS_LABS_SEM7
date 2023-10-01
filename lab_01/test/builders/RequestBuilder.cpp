#include "RequestBuilder.h"

RequestBuilder::RequestBuilder()
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
RequestBuilder::~RequestBuilder()
{}

RequestBuilder& RequestBuilder::withId(int id)
{
    this->id = id;
    return *this;
}
RequestBuilder& RequestBuilder::withClient(int client_id)
{
    this->client_id = client_id;
    return *this;
}
RequestBuilder& RequestBuilder::withProduct(int product_id)
{
    this->product_id = product_id;
    return *this;
}
RequestBuilder& RequestBuilder::withManager(int manager_id)
{
    this->manager_id = manager_id;
    return *this;
}

RequestBuilder& RequestBuilder::withSum(float sum)
{
    this->sum = sum;
    return *this;
}
RequestBuilder& RequestBuilder::withDuration(int duration)
{
    this->duration = duration;
    return *this;
}
RequestBuilder& RequestBuilder::withDate(timereq_t date)
{
    this->date = date;
    return *this;
}
RequestBuilder& RequestBuilder::withState(State_t state)
{
    this->state = state;
    return *this;
}
Request RequestBuilder::build()
{
    Request req = Request(this->id, this->client_id, this->product_id, this->manager_id, this->sum,
    this->duration, this->date, this->state);
    return req;
}