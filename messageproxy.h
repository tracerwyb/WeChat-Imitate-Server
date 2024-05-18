#ifndef MESSAGEPROXY_H
#define MESSAGEPROXY_H
#include "messagebroker.h"
#include <map>
#include "messageinterface.h"
#include "message.h"
#include <vector>

class Message;
class MessageProxy : MessageInterface
{
public:
    void storeMessage(unsigned int receiverid,
                      unsigned int senderid,
                      std::string content,
                      time_t dateTime,
                      std::string type);
    void storeMessage(unsigned int receiverid,
                      unsigned int senderid,
                      std::vector<unsigned char> content,
                      time_t dateTime,
                      std::string type);
    std::vector<nlohmann::json> pushMessage(unsigned int receiverid);

    void deleteMsg();

    nlohmann::json getAbstract();
    std::vector<unsigned char> getByteAbstract();

private:
    Message _message;
    std::vector<Message> m_msg_sequence;
    std::vector<nlohmann::json> m_msg_sequence_json;
};

#endif
