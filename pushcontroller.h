#ifndef PUSHCONTROLLER_H
#define PUSHCONTROLLER_H
#include "controller.h"
#include "message.h"

class PushController : Controller {
public:
    std::vector<unsigned char> pushMessage(nlohmann::json msg_json);

    void pushAddFriendRequest();
};

#endif
