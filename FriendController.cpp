#include "FriendController.h"
#include "UserBroker.h"
#include "UserProxy.h"
#include "netWork.h"
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;
FriendController *FriendController::m_friendController;

FriendController::FriendController()
    : userproxy{new UserProxy}
{}

FriendController *FriendController::getInstance()
{
    if (m_friendController == nullptr) {
        m_friendController = new FriendController();
    }
    return m_friendController;
}

UserInterface *FriendController::findFriendById(int friend_id)
{
    return userproxy->findFriendByID(friend_id);
}

void FriendController::storeAddFriendInfo(USER_ID user_id, USER_CONN user_conn)
{
    if (!UserBroker::getInstance()->storeFriendRequest(user_id, user_conn))
        std::cerr << "store friend request failed!";
}

void FriendController::pushAddFriendRequest(int user_id, int friend_id)
{
    json friendRequest;

    friendRequest["type"] = {"FriendRequest"};
    friendRequest["user_id"] = {user_id};
    friendRequest["friend_id"] = {friend_id};

    std::string buf = friendRequest.dump();
    if (int friendConn = User::findUserConn(friend_id)) {
        Network network;
        network.sendMessage(friendConn, buf.data());
    }

    storeAddFriendInfo(user_id, friend_id);
}

void FriendController::updateFriendList(int user_id, int friend_id, int state)
{
    (new UserProxy())->updateFriendList(user_id, friend_id, state);
}
