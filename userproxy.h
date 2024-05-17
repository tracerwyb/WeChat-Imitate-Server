#ifndef USERPROXY_H
#define USERPROXY_H

#include "user.h"
#include "userinterface.h"

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
};

#endif
