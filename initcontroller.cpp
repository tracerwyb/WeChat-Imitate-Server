#include "initcontroller.h"
#include "relationalbroker.h"
#include "userproxy.h"

#include <QDebug>
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

InitController *InitController::m_initController;

InitController::InitController() {}

InitController *InitController::getInstance()
{
    if (m_initController == nullptr) {
        m_initController = new InitController();
    }
    return m_initController;
}

void InitController::recordUserConn(USER_ID user_id, USER_CONN user_conn)
{
    (new UserProxy())->updateMusers(user_id, user_conn);
}

void InitController::initDatabase()
{
    (new RelationalBroker())->initDataBase();
}

void InitController::createWorkDir()
{
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
}
