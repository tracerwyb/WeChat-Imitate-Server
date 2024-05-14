#ifndef USERPROXY_H
#define USERPROXY_H

#include "User.h"
#include "UserInterface.h"

class UserProxy : public User
{
public:
    void modifyBaseInfo();
    void updateFriendList(int user_id, int friend_id, int state);
    void logOff();
    User *findFriendByID(int friend_id);
};

#endif
