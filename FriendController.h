#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include "Controller.h"
#include "User.h"
#include "UserInterface.h"
class FriendController : public Controller
{
public:
    static FriendController *getInstance();
    ~FriendController();

    UserInterface *findFriendById(int friend_id);
    void storeAddFriendInfo(USER_ID user_id, USER_CONN user_conn);
    void pushAddFriendRequest(int userConn, int friendConn);
    void updateFriendList(int user_id, int friend_id, int state);

private:
    static FriendController *m_friendController;
    UserInterface *userproxy;
    FriendController();
};

#endif
