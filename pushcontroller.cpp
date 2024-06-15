#include "pushcontroller.h"
#include "network.h"
#include "user.h"
#include "userproxy.h"
#include <fstream>
#include <iostream>

PushController *PushController::m_pushController;

PushController::PushController() {}

PushController *PushController::getInstance()
{
    if (m_pushController == nullptr) {
        m_pushController = new PushController();
    }
    return m_pushController;
}

void PushController::pushMessage(json msg, int object)
{
    Network network;
    std::string msg_str = msg.dump();
    network.sendMessage(object, msg_str.data());
}

void PushController::pushAddFriendRequest(int user_id, int friend_id)
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
}
//推送-----------------
nlohmann::json PushController::pushUserAvatar(int userId)
{
    // std::cout << "PushController::pushUserAvatar" << std::endl;
    UserProxy u;
    return u.findFriendListAvatar(userId);
}

nlohmann::json PushController::pushUserFriendsInfo(int userId)
{
    UserProxy u;
    return u.findUserFriendsInfo(userId);
}
//--------------------
std::vector<unsigned char> PushController::pushMessage(nlohmann::json msg_json)
{
    std::string type = msg_json["MessageType"];
    if (type == "Audio" || type == "Vedio" || type == "Picture") {
        std::string filePath = msg_json["essageContent"];
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
        }
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
        file.close();
        if (buffer.empty()) {
            std::cerr << "Failed to read file: " << filePath << std::endl;
        }
        std::cout << "Read " << buffer.size() << " bytes from file." << std::endl;
        return buffer;
    } else {
        std::vector<unsigned char> buffer;
        return buffer;
    }
}
