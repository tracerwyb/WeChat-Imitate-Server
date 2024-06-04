#include "userproxy.h"

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
