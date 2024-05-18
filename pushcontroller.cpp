#include "pushcontroller.h"
#include "network.h"
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
    network.sendMessage(object, msg_str.data(), msg_str.length());
}

void PushController::pushAddFriendRequest(int userID, int friendID)
{
    // netWork
}

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
