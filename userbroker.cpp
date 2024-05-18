#include "userbroker.h"
#include "relationalbroker.h"
#include <time.h>

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
    return storeQueryResultToJson(user);
}

bool UserBroker::isUserIDExists(USER_ID user_id)
{
    std::string command;
    command = "select * from Users where UserID = " + std::to_string(user_id) + ";";
    return RelationalBroker::query(command).size();
}

json UserBroker::storeQueryResultToJson(const mysqlpp::StoreQueryResult &user)
{
    json jsonArray;
    for (size_t i = 0; i < user.num_rows(); ++i) {
        json jsonObject;
        for (size_t j = 0; j < user.num_fields(); ++j) {
            jsonObject[user.field_name(j)] = user[i][j].c_str();
        }
        jsonArray.push_back(jsonObject);
    }
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
