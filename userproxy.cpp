#include "userproxy.h"
#include "userbroker.h"

void UserProxy::modifyBaseInfo() {
	
}

void UserProxy::updateMusers(USER_ID user_id, USER_CONN user_conn)
{
    User::updateMUsers(user_id, user_conn);
}

void UserProxy::updateFriendList(USER_ID user_id, USER_ID friend_id, int state)
{
    (new User(user_id))->updateFriendList(friend_id, state);
}

void UserProxy::logOff() {
	
}

nlohmann::json UserProxy::findFriendByID(USER_ID friend_id)
{
    return ((new User(friend_id))->getInfoFromDB());
}

json UserProxy::toJson(User *user)
{
    return user->toJson();
}

int UserProxy::findUserConn(USER_ID user_id)
{
    return User::findUserConn(user_id);
}

bool UserProxy::isFriend(USER_ID user_id, USER_ID friend_id)
{
    User user(user_id);
    return user.isFriend(friend_id);
}

nlohmann::json UserProxy::findFriendListAvatar(int userId)
{
    std::vector<std::string> friendList = UserBroker::getInstance()->findFriendList(userId);

    std::map<std::string, std::string> friendAvatarList = UserBroker::getInstance()
                                                              ->findFriendListAvatar(friendList);
    nlohmann::json json_array = nlohmann::json::array();
    for (auto &t : friendAvatarList) {
        json obj;
        obj["request_type"] = "initUsersAvatar";
        obj["UserId"] = t.first;
        obj["UserAvatar"] = t.second;
        json_array.push_back(obj);
    }
    return json_array;
}

json UserProxy::findUserFriendsInfo(int userId)
{
    nlohmann::json json_array = nlohmann::json::array();
    std::vector<std::string> friendList = UserBroker::getInstance()->findFriendList(userId);
    for (auto &t : friendList) {
        json obj = UserBroker::getInstance()->findUserInfo(std::stoi(t));
        obj["request_type"] = "initFriendInfo";
        json_array.push_back(obj);
    }
    return json_array;
}
