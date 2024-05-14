#include "PushController.h"

PushController *PushController::m_pushController;

PushController::PushController() {}

PushController *PushController::getInstance()
{
    if (m_pushController == nullptr) {
        m_pushController = new PushController();
    }
    return m_pushController;
}

void PushController::pushMessage() {
	
}

void PushController::pushAddFriendRequest(int userID, int friendID)
{
    // netWork
}
