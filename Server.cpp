#include "Server.h"

Server::Server()
{
    ThreadPool m_threadPool;
    InitController *m_ic;
    MessageController *m_mc;
    PushController *m_pc;
    FriendController *m_fc;
    m_ic = ControllerFactory::getInstance()->createInitController();
    m_mc = ControllerFactory::getInstance()->createMessageController();
    m_pc = ControllerFactory::getInstance()->createPushController();
    m_fc = ControllerFactory::getInstance()->createFriendController();
}

void Server::start() {}

void Server::processClientRequest(int &fd) {}

bool Server::receive() {}

void Server::send() {}
