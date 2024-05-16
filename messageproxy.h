#ifndef MESSAGEPROXY_H
#define MESSAGEPROXY_H

#include "Message.h"
#include "MessageInterface.h"
#include <vector>

class MessageProxy : MessageInterface
{
public:
    std::vector<Message> m_msgSequence;

    json sendMessage();

    void deleteMsg();
};

#endif
