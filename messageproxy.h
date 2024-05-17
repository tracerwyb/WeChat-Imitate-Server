#ifndef MESSAGEPROXY_H
#define MESSAGEPROXY_H

#include "messageinterface.h"
#include "message.h"
#include <vector>

class MessageProxy : MessageInterface
{
public:
    std::vector<Message> m_msgSequence;

    json sendMessage();

    void deleteMsg();
};

#endif
