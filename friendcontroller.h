#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include "controller.h"
#include "user.h"
#include "userproxy.h"

class FriendController : public Controller
{
public:
    static FriendController *getInstance();
    ~FriendController();

    json findFriendById(int friend_id);
    void storeAddFriendInfo(int user_id, int friend_id);
    void pushAddFriendRequest(int user_id, int friend_id);
    void updateFriendList(int user_id, int friend_id, int state);
    json isFriend(int user_id, int friend_id);

private:
    static FriendController *m_friendController;
    UserProxy *userproxy;
    FriendController();
};

#endif
