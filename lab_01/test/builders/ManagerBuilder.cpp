#include "ManagerBuilder.h"

ManagerBuilder::ManagerBuilder()
{
    this->id = NONE;
    this->user_id = NONE;
    this->bank_id = NONE;
}

ManagerBuilder::~ManagerBuilder()
{}

ManagerBuilder& ManagerBuilder::withId(int id)
{
    this->id = id;
    return *this;
}

ManagerBuilder& ManagerBuilder::withUser(int user_id)
{
    this->user_id = user_id;
    return *this;
}

ManagerBuilder& ManagerBuilder::withBank(int bank_id)
{
    this->bank_id = bank_id;
    return *this;
}

Manager ManagerBuilder::build()
{
    Manager man = Manager(this->id, this->user_id, this->bank_id);
    return man;
}