#include "messagebroker.h"
#include "message.h"
#include <string>
static MessageBroker *m_messageBroker = nullptr;
MessageBroker::MessageBroker() {}

MessageBroker *MessageBroker::getInstance()
{
    if (m_messageBroker == nullptr) {
        m_messageBroker = new MessageBroker();
    }
    return m_messageBroker;
}

bool MessageBroker::addNewMessage(unsigned int receiverid,
                                  unsigned int senderid,
                                  std::string content,
                                  std::string dateTime,
                                  std::string type)
{
    // time(&dateTime);
    // char time_buffer[20]; // 足够存储日期和时间的字符数组
    // std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", localtime(&dateTime));

    this->command = "INSERT INTO Message (MessageID, SenderId, "
                    "SendTime,ReceiverId,MessageContent,MessageType)VALUES(null,"
                    + std::to_string(senderid) + ",'" + dateTime + "'," + std::to_string(receiverid)
                    + ",'" + content + "','" + type + "');";
    RelationalBroker::update(command);
    return true;
}

bool MessageBroker::deleteMessage(unsigned int receiverid)
{
    this->command = "DELETE FROM Message WHERE ReceiverId=" + std::to_string(receiverid);
    RelationalBroker::update(command);
    return true;
}

//RelationalBroker::query(std::string command)
std::vector<Message> MessageBroker::getMessage(unsigned int receiverid)
{
    std::cout << receiverid << std::endl;
    std::string command = "SELECT * FROM Message WHERE ReceiverId=" + std::to_string(receiverid)
                          + ";";
    mysqlpp::StoreQueryResult res = RelationalBroker::query(command);
    // std::cout << "in messagebroker success get messages" << std::endl;
    std::vector<Message> msgs;
    for (size_t i = 0; i < res.num_rows(); ++i) {
        mysqlpp::Row row = res[i];
        unsigned int _receiverid = row["ReceiverId"];
        unsigned int _senderid = row["SenderId"];
        std::string _datatime = row["SendTime"].c_str();
        std::string _type = row["MessageType"].c_str();
        std::string _content = row["MessageContent"].c_str();

        Message msg(_receiverid, _senderid, _content, _datatime, _type);
        std::cout << _receiverid << " " << _senderid << " " << _datatime << std::endl;
        msgs.push_back(msg);
    }

    return msgs;
}
