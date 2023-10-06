#include "ModelManager.h"

Manager::Manager(int id, int user_id, int bank_id) {
    this->id = id;
    this->user_id = user_id;
    this->bank_id = bank_id;
}

Manager::Manager() {
    this->id = NONE;
    this->user_id = NONE;
    this->bank_id = NONE;
}

Manager::~Manager()
{}

int Manager::getID()
{
    return this->id;
}
int Manager::getUserID() {
    return this->user_id;
}

int Manager::getBankID() {
    return this->bank_id;
}

void Manager::setBankID(int bank_id) {
    this->bank_id = bank_id;
}