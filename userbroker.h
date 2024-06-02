#ifndef USERBROKER_H
#define USERBROKER_H

#include "relationalbroker.h"
#include "nlohmann/json.hpp"

using nlohmann::json;

#define USER_ID unsigned int
#define USER_CONN int
class User;

class UserBroker : public RelationalBroker
{
public:
	static UserBroker* m_userBroker;
	static UserBroker* getInstance();
    json findUser(USER_ID user_id);
    bool isFriend(USER_ID user_id, USER_ID friend_id);
    bool isUserIDExists(USER_ID user_id);
    bool storeFriendRequest(USER_ID request_sender_id, USER_ID request_recver_id);
    int modifyFriendRequest(USER_ID user_id, USER_ID friend_id, int state);
    bool addFriendRelation(USER_ID user_id, USER_ID friend_id);
    bool deleteFriendRelation(USER_ID user_id, USER_ID friend_id);
    bool logOffUser();
    bool modifyUserInfo();
    json storeQueryResultToJson_Users(const mysqlpp::StoreQueryResult &user,
                                      const std::string msg_type);
    std::string findValueOfField(const mysqlpp::StoreQueryResult &user,
                                 const std::string fieldname,
                                 int rowindex);
};

#endif
