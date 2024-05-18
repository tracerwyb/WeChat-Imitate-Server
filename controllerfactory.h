#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "friendcontroller.h"
#include "initcontroller.h"
#include "messagecontroller.h"
#include "pushcontroller.h"

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
