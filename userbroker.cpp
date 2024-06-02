#include "userbroker.h"
#include <QDebug>
#include "relationalbroker.h"
#include <iostream>
#include <mysql++/mysql++.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <time.h>

using namespace rapidjson;

UserBroker *UserBroker::m_userBroker = nullptr;

UserBroker *UserBroker::getInstance()
{
    if (m_userBroker == nullptr)
        m_userBroker = new UserBroker();
    return m_userBroker;
}

json UserBroker::findUser(USER_ID user_id)
{
    std::string command;
    command = "select * from Users where UserID = " + std::to_string(user_id) + ";";
    mysqlpp::StoreQueryResult user = RelationalBroker::query(command);
    qDebug() << user.data();
    return storeQueryResultToJson_Users(user, "user_info");
}

bool UserBroker::isFriend(USER_ID user_id, USER_ID friend_id)
{
    std::string command;
    command = "select * from Relation where (User1ID = " + std::to_string(user_id)
              + " AND User2ID = " + std::to_string(friend_id) + ") OR (User1ID = "
              + std::to_string(friend_id) + " AND User2ID = " + std::to_string(user_id) + ");";
    if (RelationalBroker::query(command).size() != 0) {
        return true;
    }
    return false;
    // size == 0 -> return false
}

bool UserBroker::isUserIDExists(USER_ID user_id)
{
    std::string command;
    command = "select * from Users where UserID = " + std::to_string(user_id) + ";";
    return RelationalBroker::query(command).size();
}

std::string UserBroker::findValueOfField(const mysqlpp::StoreQueryResult &user,
                                         const std::string fieldName,
                                         int rowIndex)
{
    std::string fieldValue;

    if (!user.empty() && rowIndex >= 0 && rowIndex < user.size()) {
        // 使用指定行的字段值
        const mysqlpp::Row &currentRow = user[rowIndex];

        // 使用字段名获取字段的索引
        int fieldIndex = user.field_num(fieldName);

        // 检查字段是否存在
        if (fieldIndex != -1) {
            // 获取字段值
            fieldValue = currentRow[fieldIndex].data();
            // 输出字段的值
            // std::cout << "Value of field " << fieldName << ": " << fieldValue << std::endl;
        } else {
            std::cerr << "Field '" << fieldName << "' not found in the result set." << std::endl;
        }
    } else {
        std::cerr << "Result set is empty or row index is out of range." << std::endl;
    }

    return fieldValue;
}

json UserBroker::storeQueryResultToJson_Users(const mysqlpp::StoreQueryResult &user,
                                              const std::string msgType)
{
    json jsonArray;

    // 遍历每一行并将字段值存储到 JSON 对象中
    for (size_t i = 0; i < user.size(); ++i) {
        json userData;
        userData["request_type"] = msgType;
        userData["friendID"] = findValueOfField(user, "UserID", i);
        userData["nickname"] = findValueOfField(user, "U_Nickname", i);
        userData["avatar_path_"] = findValueOfField(user, "U_Avater", i);
        userData["gender"] = findValueOfField(user, "U_Gender", i);
        userData["area"] = findValueOfField(user, "U_Area", i);
        userData["signature"] = findValueOfField(user, "U_Signature", i);
        userData["memo"]
            = findValueOfField(user,
                               "U_Nickname",
                               i); // 注意：此处 fieldName 使用了 "U_Nickname"，而不是 "memo"

        jsonArray = userData;
    }

    qDebug() << jsonArray.dump();
    return jsonArray;
}

bool UserBroker::storeFriendRequest(USER_ID request_sender_id, USER_ID request_recver_id)
{
    time_t tim;
    time(&tim);

    char time_buffer[20]; // 足够存储日期和时间的字符数组
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", localtime(&tim));

    // add new friend request record
    std::string command_store;
    command_store = "INSERT INTO FriendRequest (RequestID, RequestSenderID, RequestReceiverID, "
                    "RequestTime, state)VALUES (null,"
                    + std::to_string(request_sender_id) + "," + std::to_string(request_recver_id)
                    + ",'" + std::string(time_buffer) + "', 0);";
    // std::cout << command_store << std::endl;
    update(command_store);
    return true;
}

int UserBroker::modifyFriendRequest(USER_ID user_id, USER_ID friend_id, int state)
{
    // update the state of a friend request
    std::string command_request;
    command_request = "update FriendRequest set state=" + std::to_string(state)
                      + " where (RequestSenderID=" + std::to_string(user_id)
                      + " AND RequestReceiverID=" + std::to_string(friend_id)
                      + ") OR (RequestSenderID = " + std::to_string(friend_id)
                      + " AND RequestReceiverID = " + std::to_string(user_id) + ");";

    // std::cout << command_request << std::endl;
    update(command_request);
    return state;
}

bool UserBroker::addFriendRelation(USER_ID user_id, USER_ID friend_id)
{
    //update Relation sheet
    time_t tim;
    time(&tim);

    char time_buffer[20]; // 足够存储日期和时间的字符数组
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", localtime(&tim));

    std::string command_relation;
    command_relation = "INSERT INTO Relation (RelationID, User1ID, User2ID, BuildTime)"
                       "VALUES(null,"
                       + std::to_string(user_id) + "," + std::to_string(friend_id) + ",'"
                       + std::string(time_buffer) + "');";
    update(command_relation);

    // std::cout << command_relation << std::endl;
    // update FriendRequest sheet
    modifyFriendRequest(user_id, friend_id, 1);

    return true;
}

bool UserBroker::deleteFriendRelation(USER_ID user_id, USER_ID friend_id)
{
    //delete specify relation record from Relation sheet

    std::string command;
    command = "delete FROM Relation WHERE (User1ID = " + std::to_string(user_id) + " AND User2ID = "
              + std::to_string(friend_id) + ") OR (User1ID = " + std::to_string(friend_id)
              + " AND User2ID = " + std::to_string(user_id) + ");";

    update(command);

    // std::cout << command << std::endl;
    // update FriendRequest sheet
    modifyFriendRequest(user_id, friend_id, -1);

    return true;
}

bool UserBroker::logOffUser() {
	
}

bool UserBroker::modifyUserInfo() {
	
}
