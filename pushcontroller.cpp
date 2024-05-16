#include "pushcontroller.h"
#include <fstream>
#include <iostream>
/*
std::vector<unsigned char> Message::getByteAbstract()
{
    if (this->type == "Audio" || this->type == "Vedio" || this->type == "Picture") {
        std::string filePath = this->content;
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
    j["ReceiverId "] = this->receiverid;
    j["SenderId"] = this->senderid;
    j["SendTime"] = this->dateTime;
    j["MessageType"] = this->type;
    j["essageContent"] = this->content;
*/

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

void PushController::pushAddFriendRequest() {}
