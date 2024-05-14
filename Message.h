#ifndef MESSAGE_H
#define MESSAGE_H

#include "MessageInterface.h"
#include <nlohmann/json.hpp>
#include <string>
#include <time.h>

using nlohmann::json;

class MessageProxy;

class Message : public MessageInterface
{
private:
    MessageProxy *message;
    unsigned int receiverid;
    unsigned int senderid;
    std::string type;
    std::string content;
    time_t dateTime;

public:
    json processMessage();
};

#endif
