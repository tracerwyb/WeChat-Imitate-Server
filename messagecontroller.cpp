#include "messagecontroller.h"
#include "message.h"
#include "messagebroker.h"
#include "messageproxy.h"

MessageController *MessageController::m_msgController;

MessageController *MessageController::getInstance() {
    if (m_msgController == nullptr) {
        m_msgController = new MessageController();
    }
    return m_msgController;
}
//Message会将byte处理为path-string
void MessageController::storeMessageInfo(unsigned int receiverid,
                                         unsigned int senderid,
                                         std::vector<unsigned char> byte_Stream,
                                         std::string dateTime,
                                         std::string type)
{
    Message msg;
    std::string path = msg.handleByteStreamContent(byte_Stream, type);
    MessageProxy m_proxy;
    m_proxy.storeMessage(receiverid, senderid, path, dateTime, type);
}
void MessageController::storeMessageInfo(unsigned int receiverid,
                                         unsigned int senderid,
                                         std::string content,
                                         std::string dateTime,
                                         std::string type)
{
    MessageProxy m_proxy;
    m_proxy.storeMessage(receiverid, senderid, content, dateTime, type);
}

std::vector<nlohmann::json> MessageController::pushMessage(unsigned int receiverid)
{
    MessageProxy m_proxy;
    return (m_proxy.pushMessage(receiverid));
    //消息包含receiverid, senderid, content, dateTime
    //从数据库中读取消息后json化后调用push推送，推送成功后删除消息，可以是在sever那里执行
}
