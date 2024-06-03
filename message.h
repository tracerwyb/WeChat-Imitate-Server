#ifndef MESSAGE_H
#define MESSAGE_H
#include "messageinterface.h"
#include <nlohmann/json.hpp>
#include <string>

using namespace std;

class MessageInterface;

class Message : MessageInterface
{
private:
    unsigned int receiverid;
    unsigned int senderid;
    std::string type;
    std::string content;
    std::string dateTime;

public:
    Message();
    Message(unsigned int _receiverid,
            unsigned int _senderid,
            std::string _content,
            std::string _dateTime,
            std::string _type);
    nlohmann::json getAbstract();
    std::vector<unsigned char> getByteAbstract();
    std::string handleByteStreamContent(std::vector<unsigned char> byte_Stream, std::string type);
};

#endif
