#include "UserProxy.h"

void UserProxy::modifyBaseInfo() {
	
}

void UserProxy::updateFriendList(int user_id, int friend_id, int state)
{
    (new User(user_id))->updateFriendList(friend_id, state);
}

void UserProxy::logOff() {
	
}

nlohmann::json UserProxy::findFriendByID(int friend_id)
{
    return ((new User(friend_id))->getInfoFromDB());
}

json UserProxy::toJson(User *user)
{
    return user->toJson();
}

int UserProxy::findUserConn(int user_id)
{
    return User::findUserConn(user_id);
}
