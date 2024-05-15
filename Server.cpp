#include "Server.h"
#include <iostream>

#define ADDFRIEND 1
#define DELETEFRIEND -1
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

    // test
    int user_id, friend_id;
    user_id = 20412785;
    friend_id = 20209834;
    // if client search a person by id

    std::cout << m_fc->findFriendById(friend_id); // User*
    // get that person infomation
    // User user;
    // m_pc->pushMessage(user.getInfoFromDB(), user.findUserConn(friend_id));
    // pretend server has received message(add friend request) from client (message with user_id and friend_id)
    // m_fc->pushAddFriendRequest(user_id, friend_id);
    m_fc->storeAddFriendInfo(user_id, friend_id);

    // if friend accept friend_request: update db sheet FriendRequest and Relation
    m_fc->updateFriendList(user_id, friend_id, DELETEFRIEND);
}

void Server::start() {}

void Server::processClientRequest(int &fd) {}

bool Server::receive() {}

void Server::send() {}
