#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "FriendController.h"
#include "InitController.h"
#include "MessageController.h"
#include "PushController.h"

class ControllerFactory {
public:
    static ControllerFactory *getInstance();
    ~ControllerFactory();

    InitController *createInitController();
    MessageController *createMessageController();
    PushController *createPushController();
    FriendController *createFriendController();

private:
    static ControllerFactory *m_controllerFactory;
    ControllerFactory();
};

#endif
