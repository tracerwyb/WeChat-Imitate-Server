#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "relationalbroker.h"

class MessageBroker : RelationalBroker
{
public:
    static MessageBroker *m_msgBroker;

    static MessageBroker *getInstance();

    bool addNewMessage();

    bool delMsgForUser();

    bool deleteMessage();
};

#endif
