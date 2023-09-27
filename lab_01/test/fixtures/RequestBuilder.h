#ifndef PPO_REQUESTBUILDER_H
#define PPO_REQUESTBUILDER_H

#include "../../src/business_logic/models/ModelRequest.h"
#include "../../src/business_logic/rules/RequestRules.h"

class RequestBuilder {
    private:
        int id;
        int client_id;
        int product_id;
        int manager_id;
        float sum;
        int duration;
        timereq_t date;
        State_t state;
    
    public:
        RequestBuilder();
        ~RequestBuilder();
        RequestBuilder& withId(int id);
        RequestBuilder& withClient(int client_id);
        RequestBuilder& withProduct(int product_id);
        RequestBuilder& withManager(int manager_id);
        RequestBuilder& withSum(float sum);
        RequestBuilder& withDuration(int duration);
        RequestBuilder& withDate(timereq_t date);
        RequestBuilder& withState(State_t state);
        Request build();
};

#endif //PPO_REQUESTBUILDER_H