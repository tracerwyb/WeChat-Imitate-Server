#include "messageproxy.h"

void MessageProxy::storeMessage(unsigned int receiverid,
                                unsigned int senderid,
                                std::string content,
                                std::string dateTime,
                                std::string type)
{
    auto broker = MessageBroker::getInstance();
    broker->addNewMessage(receiverid, senderid, content, dateTime, type);
}
void MessageProxy::storeMessage(unsigned int receiverid,
                                unsigned int senderid,
                                std::vector<unsigned char> content,
                                std::string dateTime,
                                std::string type)
{
    auto broker = MessageBroker::getInstance();
    std::string _content = _message.handleByteStreamContent(content, type);
    broker->addNewMessage(receiverid, senderid, _content, dateTime, type);
}

//一次性读取;一次性发送/多次发送for循环
std::vector<nlohmann::json> MessageProxy::pushMessage(unsigned int receiverid)
{
    auto broker = MessageBroker::getInstance();
    m_msg_sequence = broker->getMessage(receiverid);
    int size = m_msg_sequence.size();
    for (int i = 0; i < size; i++) {
        m_msg_sequence_json.push_back(m_msg_sequence[i].getAbstract());
    }
    return m_msg_sequence_json;
}

void MessageProxy::deleteMsg() {}
