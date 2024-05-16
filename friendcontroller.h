#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include "controller.h"
#include "User.h"
#include "UserInterface.h"
class FriendController : public Controller
{
public:
    static FriendController *getInstance();
    ~FriendController();

    json findFriendById(int friend_id);
    void storeAddFriendInfo(int user_id, int friend_id);
    void pushAddFriendRequest(int user_id, int friend_id);
    void updateFriendList(int user_id, int friend_id, int state);

private:
    static FriendController *m_friendController;
    UserInterface *userproxy;
    FriendController();
};

#endif
