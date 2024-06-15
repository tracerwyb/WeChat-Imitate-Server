#ifndef USERPROXY_H
#define USERPROXY_H

#include "user.h"
#include "userinterface.h"
#include <string>
#include <vector>
class UserProxy : public User
{
public:
    void modifyBaseInfo();
    void updateFriendList(USER_ID user_id, USER_ID friend_id, int state);
    void logOff();
    int findUserConn(USER_ID user_id);
    void updateMusers(USER_ID user_id, USER_CONN user_conn);
    json findFriendByID(USER_ID friend_id);
    json toJson(User *user);
    void initFriendList();
    bool isFriend(USER_ID user_id, USER_ID friend_id);
    //查找到用户的朋友
    nlohmann::json findFriendListAvatar(int userId);
    nlohmann::json findUserFriendsInfo(int userId);
};

#endif
