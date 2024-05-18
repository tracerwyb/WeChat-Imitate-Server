#include "relationalbroker.h"
#include <iostream>
#include <mysql/mysql.h>

std::unique_ptr<mysqlpp::Connection> RelationalBroker::m_connection = NULL;

RelationalBroker::RelationalBroker()
{
    buildConnect();
}

bool RelationalBroker::buildConnect()
{
    //init connection
    std::unique_ptr<mysqlpp::Connection> conn = std::make_unique<mysqlpp::Connection>(false);
    if (conn->connect("smallchat", "localhost", "root", "123456"))
        std::cout << "Connect Sucessfully" << std::endl;
    else
        std::cout << "Connect Unsucessfully" << std::endl;
    m_connection = std::move(conn);

    return false;
}

void RelationalBroker::initDataBase()
{
    //create table
    try {
        this->query("CREATE TABLE FriendRequest(RequestID INT UNSIGNED PRIMARY KEY "
                    "AUTO_INCREMENT,RequestSenderID INT "
                    "UNSIGNED,RequestReceiverID INT UNSIGNED,RequestTime DATETIME, state INT);");

        this->query("CREATE TABLE Users (UserID INT UNSIGNED PRIMARY KEY AUTO_INCREMENT,U_Nickname "
                    "VARCHAR(20), U_Avater "
                    "VARCHAR(50) ,U_Gender CHAR(1),U_Area VARCHAR(20),U_Signature "
                    "VARCHAR(30))AUTO_INCREMENT = 5;");

        this->query(
            "CREATE TABLE Relation(RelationID INT UNSIGNED PRIMARY KEY AUTO_INCREMENT, User1ID INT "
            "UNSIGNED,User2ID INT UNSIGNED,BuildTime DATETIME);");

        this->query(
            "CREATE TABLE Message(MessageID INT UNSIGNED PRIMARY KEY AUTO_INCREMENT, SendTime "
            "DATETIME,SenderId INT UNSIGNED,ReceiverId INT UNSIGNED,MessageContent VARCHAR(250));");

        this->query("INSERT INTO Users "
                    "(UserID, U_Nickname, U_Avater, U_Gender, U_Area, U_Signature)VALUES"
                    "(20209834, '85', 'path', '女', '重庆', '罪恶没有假期，正义便无暇休憩'),"
                    " (20419934, '坐看云起时', 'path', '女', '重庆', '以雷霆击碎黑暗'),  "
                    "(20726334, 'hahaha', 'path', '女', '重庆', '我叫hahaha');");

        this->query("INSERT INTO FriendRequest (RequestID, RequestSenderID, RequestReceiverID, "
                    "RequestTime, state)VALUES "
                    "(1, 20209834, 20419934, '2024-04-26 17:20:00', -1),"
                    "(2, 20419934, 20419934, '2024-04-26 17:20:00', 0),"
                    "(3, 20726334, 20419934, '2024-04-26 17:20:00', 1);");

        this->query("INSERT INTO Relation (RelationID, User1ID, User2ID, BuildTime)VALUES (1, "
                    "20209834, 20419934, '2024-04-26 17:20:00'), (2, 20419934, 20419934, "
                    "'2024-04-26 17:20:00'), (3, 20726334, 20419934, '2024-04-26 17:20:00');");

        this->query("INSERT INTO Message (MessageID, SendTime, SenderId,ReceiverId, "
                    "MessageContent)VALUES(1, '2024-04-26 17:20:00', "
                    "'20419934', '20419934','hello, this is kangkang'),(2, '2024-04-26 17:23:00', "
                    "'20726334','20419934', "
                    "'hello world'),"
                    "(3, '2024-04-26 17:24:00', '20209834','20419934', 'hello qt');");

    } catch (mysqlpp::Exception e) {
        std::cout << e.what();
    }
}

mysqlpp::StoreQueryResult RelationalBroker::query(std::string command)
{
    mysqlpp::StoreQueryResult res;
    try {
        mysqlpp::Query query = m_connection->query();
        query << command;
        res = query.store();
    } catch (mysqlpp::BadQuery e) {
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    //显示数据
    mysqlpp::StoreQueryResult::const_iterator it; // 迭代器
    size_t numFields = res.num_fields();
    for (it = res.begin(); it != res.end(); ++it) {
        for (size_t j = 0; j < numFields; ++j) {
            mysqlpp::Row row = *it;
            // 获取每个字段的值并进行相应处理
            std::cout << row[j] << "\t";
        }
        std::cout << std::endl;
        // std::cout << '\t' << row[0] << row[1] << std::endl;
    }
    return res;
}

void RelationalBroker::update(std::string command)
{
    try {
        mysqlpp::Query query = m_connection->query();
        std::cout << command << std::endl;
        query << command;
        query.store();
    } catch (std::exception e) {
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
}
