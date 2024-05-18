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
                                  time_t dateTime,
                                  std::string type)
{
    time(&dateTime);
    char time_buffer[20]; // 足够存储日期和时间的字符数组
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", localtime(&dateTime));

    this->command = "INSERT INTO Message (MessageID, SenderId, "
                    "SendTime,ReceiverId,MessageContent,MessageType)VALUES(null,"
                    + std::to_string(senderid) + ",'" + std::string(time_buffer) + "',"
                    + std::to_string(receiverid) + ",'" + content + "','" + type + "');";
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
    this->command = "SELECT RECEIVERID=" + std::to_string(receiverid) + " from Message;";
    mysqlpp::StoreQueryResult res = RelationalBroker::query(command);

    //处理数据
    std::vector<Message> msgs;
    for (size_t i = 0; i < res.num_rows(); ++i) {
        mysqlpp::Row row = res[i];

        // 获取每个字段的值
        unsigned int _receiverid = row["ReceiverId"];
        unsigned int _senderid = row["SenderId "];
        time_t _dateTime = row["SendTime "];

        char _type[10];
        char _content[250];
        strcpy(_type, row["MessageType "]);
        strcpy(_content, row["MessageContent "]);
        ;
        Message msg(_receiverid, _senderid, std::string(_content), _dateTime, std::string(_type));
        msgs.push_back(msg);
        // 输出字段值
    }
    return msgs;
}
