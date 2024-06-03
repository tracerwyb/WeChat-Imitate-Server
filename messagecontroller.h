#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H
#include "controller.h"
#include <ctime>
#include <nlohmann/json.hpp>
#include <string>

class MessageController : Controller {
public:
    static MessageController *getInstance();
    void storeMessageInfo(unsigned int receiverid,
                          unsigned int senderid,
                          std::vector<unsigned char> byte_Stream,
                          std::string dateTime,
                          std::string type);

    void storeMessageInfo(unsigned int receiverid,
                          unsigned int senderid,
                          std::string content,
                          std::string dateTime,
                          std::string type);
    std::vector<nlohmann::json> pushMessage(unsigned int receiverid);

private:
    static MessageController *m_msgController;

};

#endif
