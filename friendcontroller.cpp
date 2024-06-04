#include "friendcontroller.h"
#include <QDebug>
#include "network.h"
#include "pushcontroller.h"
#include "userbroker.h"
#include "userproxy.h"
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

json FriendController::findFriendById(int friend_id)
{
    return userproxy->findFriendByID(friend_id);
}

json FriendController::isFriend(int user_id, int friend_id)
{
    json isfriend;
    isfriend["request_type"] = "isfriend";
    // isfriend["myid"] = user_id;
    // isfriend["friendID"] = std::to_string(friend_id);
    // qDebug() << "userproxy->isFriend(user_id, friend_id):"
    // << userproxy->isFriend(user_id, friend_id);
    if (userproxy->isFriend(user_id, friend_id)) {
        isfriend["isfriend"] = "true";
    } else {
        isfriend["isfriend"] = "false";
    }
    // qDebug() << "isfriend_bool: " << (isfriend["isfriend"]).dump();
    return isfriend;
}

void FriendController::storeAddFriendInfo(int user_id, int friend_id)
{
    if (!(UserBroker::getInstance()->storeFriendRequest(user_id, friend_id)))
        std::cerr << "store friend request failed!";
}

void FriendController::pushAddFriendRequest(int user_id, int friend_id)
{
    PushController::getInstance()->pushAddFriendRequest(user_id, friend_id);
    storeAddFriendInfo(user_id, friend_id);
}

void FriendController::updateFriendList(int user_id, int friend_id, int state)
{
    userproxy->updateFriendList(user_id, friend_id, state);
}
