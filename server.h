#ifndef SERVER_H
#define SERVER_H

#include "controllerfactory.h"
#include "threadpool.h"

class InitController;
class MessageController;
class PushController;
class FriendController;

class Server
{
private:
    ThreadPool m_threadPool;
    InitController *m_ic;
    MessageController *m_mc;
    PushController *m_pc;
    FriendController *m_fc;
    ControllerFactory *m_controllerFactory;

public:
    Server();
    void start();
    void processClientRequest(int &fd);
    bool receive();
    void send();
};

#endif
