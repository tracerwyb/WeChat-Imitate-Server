
#include "messagecontroller.h"

MessageController *MessageController::m_msgController;

MessageController::MessageController() {}

MessageController *MessageController::getInstance()
{
    if (m_msgController == nullptr) {
        m_msgController = new MessageController();
    }
    return m_msgController;
}

void MessageController::storeMessageInfo() {
	
}

void MessageController::pushMessage() {
	
}
