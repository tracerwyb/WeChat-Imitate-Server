#include "pushcontroller.h"
#include "network.h"

PushController *PushController::m_pushController;

PushController::PushController() {}

PushController *PushController::getInstance()
{
    if (m_pushController == nullptr) {
        m_pushController = new PushController();
    }
    return m_pushController;
}

void PushController::pushMessage(json msg, int object)
{
    Network network;
    std::string msg_str = msg.dump();
    network.sendMessage(object, msg_str.data(), msg_str.length());
}

void PushController::pushAddFriendRequest(int userID, int friendID)
{
    // netWork
}
