#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H
#include "relationalbroker.h"
#include <ctime>
class Message;
class MessageBroker : RelationalBroker
{
public:
    MessageBroker();
    static MessageBroker *getInstance();

    bool addNewMessage(unsigned int receiverid,
                       unsigned int senderid,
                       std::string content,
                       std::string dateTime,
                       std::string type);

    bool deleteMessage(unsigned int receiverid);
    std::vector<Message> getMessage(unsigned int receiverid);

private:
    static MessageBroker *m_netizenBroker;
    std::vector<Message> _msg;
    std::string command;
};

#endif
