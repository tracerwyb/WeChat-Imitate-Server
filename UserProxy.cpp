#include "UserProxy.h"

void UserProxy::modifyBaseInfo() {
	
}

void UserProxy::updateFriendList(int user_id, int friend_id, int state)
{
    (new User(user_id))->updateFriendList(friend_id, state);
}

void UserProxy::logOff() {
	
}

User *UserProxy::findFriendByID(int friend_id) {}
