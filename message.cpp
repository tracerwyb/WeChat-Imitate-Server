#include "message.h"
#include <ctime>
#include <fstream>
#include <iostream>
//#include <opencv4/opencv2/imgcodecs.hpp>
//#include <opencv4/opencv2/opencv.hpp>
#include <vector>

Message::Message() {}

Message::Message(unsigned int _receiverid,
                 unsigned int _senderid,
                 string _content,
                 string _dateTime,
                 string _type)
{
    this->receiverid = _receiverid;
    this->senderid = _senderid;
    this->content = _content;
    this->dateTime = _dateTime;
    this->type = _type;
}
//针对与文本聊天
nlohmann::json Message::getAbstract()
{
    nlohmann::json j;
    j["ReceiverId"] = this->receiverid;
    j["SenderId"] = this->senderid;
    j["SendTime"] = this->dateTime;
    j["MessageType"] = this->type;
    j["MessageContent"] = this->content;
    return j;
}

string Message::handleByteStreamContent(std::vector<unsigned char> byte_Stream, std::string type)
{
    time_t datetime;
    time(&datetime);

    // 将时间转换为字符串
    char time_Buffer[20]; // 足够存储日期和时间的字符数组
    std::strftime(time_Buffer, sizeof(time_Buffer), "%Y%m%d%H%M%S", std::localtime(&datetime));
    //路径要根据最终的环境更改
    std::filesystem::path current_path = std::filesystem::current_path();
    string filepath = " ";
    if (type == "Picture") {
        filepath = current_path.string() + "/UsersData/Picture/Picture_" + to_string(this->senderid)
                   + time_Buffer + ".jpg";

    } else if (type == "Vedio") {
        filepath = current_path.string() + "/UsersData/Picture/Vedio_" + to_string(this->senderid)
                   + time_Buffer + ".bin";
    } else if (type == "Audio") {
        filepath = current_path.string() + "/UsersData/Picture/Audio_" + to_string(this->senderid)
                   + time_Buffer + ".bin";
        // 打开新文件
    }

    std::ofstream newFile(filepath, std::ios::binary | std::ios::out);
    if (newFile.is_open()) {
        // 写入数据
        newFile.write(reinterpret_cast<const char *>(byte_Stream.data()), sizeof(byte_Stream));
        // 关闭文件
        newFile.close();
        std::cout << "Binary data has been written to " << filepath << " successfully."
                  << std::endl;
    } else {
        std::cerr << "Failed to open " << filepath << " for writing." << std::endl;
    }
    return filepath;
}
