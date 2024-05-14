#include "RelationalBroker.h"
#include <filesystem>
#include <iostream>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include "Server.h"

int main()
{
    RelationalBroker r;
    r.initDataBase();
    // r.query("select * from Message_UserID;");
    // r.query("select * from FriendRequest;");
    // r.query("select * from Relation;");
    // r.query("select * from Users;");

    // 获取当前工作目录s
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << current_path;

    std::string u{static_cast<std::string>(current_path) + "/UsersData"};
    char u_char[u.length() + 1];
    strcpy(u_char, u.c_str());

    mkdir(u_char, S_IRWXU | S_IRWXG | S_IRWXO);

    std::string data_name[3] = {"/Picture", "/Audio", "/Vedio"};
    for (int i = 0; i < 3; i++) {
        std::string p = {u + data_name[i]};
        char charPathArray[p.length() + 1];
        strcpy(charPathArray, p.c_str());
        try {
            //绝对路径
            if (mkdir(charPathArray, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
                std::cout << "Successfully create file" << std::endl;
            else
                std::cout << "Unsuccessfully create file" << std::endl;
        } catch (std::exception e) {
            std::cerr << e.what();
        }
    }

    Server server;

    return 0;
}
