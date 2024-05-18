#ifndef PUSHCONTROLLER_H
#define PUSHCONTROLLER_H

#include "controller.h"
class PushController : public Controller
{
public:
    static PushController *getInstance();
    ~PushController();
    void pushMessage(json msg, int conn);
    std::vector<unsigned char> pushMessage(nlohmann::json msg_json);
    void pushAddFriendRequest(int userID, int friendID);

private:
    static PushController *m_pushController;
    PushController();
};

#endif
