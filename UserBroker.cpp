#include "UserBroker.h"
#include "RelationalBroker.h"
#include <time.h>

UserBroker *UserBroker::getInstance() {}

User *UserBroker::findUser(int user_id)
{
    std::string command;
    command = "select * from Users where UserID = " + std::to_string(user_id) + ";";
    mysqlpp::StoreQueryResult user = RelationalBroker::query(command);
}

bool UserBroker::storeFriendRequest(USER_ID request_sender_id, USER_ID request_recver_id)
{
    // add new friend request record
    std::string command_store;
    command_store = "INSERT INTO FriendRequest (RequestID, RequestSenderID, RequestReceiverID, "
                    "RequestTime, state)VALUES (null,"
                    + std::to_string(request_sender_id) + "," + std::to_string(request_recver_id)
                    + ", 0);";
    return true;
}

int UserBroker::modifyFriendRequest(USER_ID user_id, USER_ID friend_id, int state)
{
    // update the state of a friend request
    std::string command_request;
    command_request = "update FriendRequest set state=" + std::to_string(state) + " where (User1ID="
                      + std::to_string(user_id) + "AND User2ID=" + std::to_string(friend_id)
                      + ") OR (User1ID = " + std::to_string(friend_id)
                      + " AND User2ID = " + std::to_string(user_id) + ");";
    update(command_request);
    return state;
}

bool UserBroker::addFriendRelation(USER_ID user_id, USER_ID friend_id)
{
    //update Relation sheet
    time_t tim;
    time(&tim);

    std::string command_relation;
    command_relation = "INSERT INTO Relation (RelationID, User1ID, User2ID, BuildTime)"
                       "VALUES(null,"
                       + std::to_string(user_id) + "," + std::to_string(friend_id) + ","
                       + ctime(&tim) + ";";
    update(command_relation);

    // update FriendRequest sheet
    modifyFriendRequest(user_id, friend_id, 1);

    return true;
}

bool UserBroker::deleteFriendRelation(USER_ID user_id, USER_ID friend_id)
{
    //delete specify relation record from Relation sheet

    std::string command;
    command = "delete * FROM Relation WHERE (User1ID = " + std::to_string(user_id)
              + " AND User2ID = " + std::to_string(friend_id) + ") OR (User1ID = "
              + std::to_string(friend_id) + " AND User2ID = " + std::to_string(user_id) + ");";

    update(command);

    return true;
}

bool UserBroker::logOffUser() {
	
}

bool UserBroker::modifyUserInfo() {
	
}
