#include "AuthStates.h"

AuthStates::AuthStates() {
    this->appState = NON_AUTH;
}

Roles AuthStates::getState() {
    return this->appState;
}

void AuthStates::toClientAuth() {
    if (this->appState == NON_AUTH)
    {
        this->appState = CLIENT;
    }
}

void AuthStates::toManagerAuth() {
    if (this->appState == NON_AUTH)
    {
        this->appState = MANAGER;
    }
}

void AuthStates::toAdminAuth() {
    if (this->appState == NON_AUTH)
    {
        this->appState = ADMIN;
    }
}

void AuthStates::toUnAuth() {
    if (this->appState != NON_AUTH)
    {
        this->appState = NON_AUTH;
    }
}

bool AuthStates::isClientAuth() {
    return this->appState == CLIENT;
}

bool AuthStates::isManagerAuth() {
    return this->appState == MANAGER;
}

bool AuthStates::isAdminAuth() {
    return this->appState == ADMIN;
}

bool AuthStates::isUnAuth() {
    return this->appState == NON_AUTH;
}