#ifndef PUSHCONTROLLER_H
#define PUSHCONTROLLER_H

#include "Controller.h"
class PushController : public Controller
{
public:
    static PushController *getInstance();
    ~PushController();
    void pushMessage();
    void pushAddFriendRequest(int userID, int friendID);

private:
    static PushController *m_pushController;
    PushController();
};

#endif
