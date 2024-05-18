#include "controllerfactory.h"

ControllerFactory *ControllerFactory::m_controllerFactory;

ControllerFactory::ControllerFactory() {}

ControllerFactory *ControllerFactory::getInstance()
{
    if (m_controllerFactory == nullptr) {
        m_controllerFactory = new ControllerFactory();
    }
    return m_controllerFactory;
}

InitController *ControllerFactory::createInitController()
{
    return InitController::getInstance();
}

MessageController *ControllerFactory::createMessageController()
{
    return MessageController::getInstance();
}

PushController *ControllerFactory::createPushController()
{
    return PushController::getInstance();
}

FriendController *ControllerFactory::createFriendController()
{
    return FriendController::getInstance();
}
