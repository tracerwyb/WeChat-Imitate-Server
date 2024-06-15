#include "server.h"
//#include <opencv4/opencv2/imgcodecs.hpp>
//#include <opencv4/opencv2/opencv.hpp>
#include "initcontroller.h"
int main()
{
    // r.query("select * from Message_UserID;");
    // r.query("select * from FriendRequest;");
    // r.query("select * from Relation;");
    // r.query("select * from Users;");
    InitController::getInstance()->initDatabase();
    Server server;
    server.start();
    
}
/*
void  init(){
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
*/
/*
bool test1_store(){
    cv::Mat src = imread("/root/项目/WeChat-Imitate-Server/resources/1.png", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "Load img failed!" << std::endl;
        return 0;
    } else {
        std::cout << "Load img success!" << std::endl;
    }
    std::vector<unsigned char> buffer;
    cv::imencode(".png", src, buffer);
    //二进制输出
    //std::cout.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    //bool success = cv::imwrite("/root/项目/WeChat-Imitate-Server/resources/output.png", src);
    //imshow("src", src);
    MessageController msgc;
    time_t datetime;
    time(&datetime);
    msgc.storeMessageInfo(123456, 654321, buffer, datetime,type);
}
*/
    /*
     
    int main()
    {
        RelationalBroker r;
        r.initDataBase();
        r.query("select * from FriendRequest ;");
        r.query("select * from Message;");
        r.query("select * from Relation;");
        r.query("select * from Users;");
        MessageController msgc;
        std::vector<nlohmann::json> msgs = msgc.pushMessage(123456);
        int size = msgs.size();
        PushController pc;
        for (int i = 0; i < size; i++) {
            //发送msgs[i]json文件
            std::vector<unsigned char> buffer = pc.pushMessage(msgs[i]);
            if (buffer.size() != 0)
                //发送字节流而
                int i = 0;
        }
        return 0;
    }
}

/*
// zhangjing main test
#include "network.h"
#include "message.h"
#include "task.h"
#include <QDebug>
#include <sys/ioctl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <QThreadPool>
int main(int argc, char *argv[])
{
    Network network;
    network.createSocket();//

    QThreadPool::globalInstance()->setMaxThreadCount(5);

    while(1){
        int cnnfd=network.acceptSocket();
        Task* ts=new Task(cnnfd); //传入连接套接字描述符，任务函数读取这条消息，找到接收者id并查找套接字描述符转发
        QThreadPool::globalInstance()->start(ts);  //将请求放入线程池的任务队列中，等待线程执行
    }
}
*/
