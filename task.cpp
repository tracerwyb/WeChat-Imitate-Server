#include "task.h"
#include <QDebug>
#include "network.h"
#include "user.h"
#include "userproxy.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

Task::Task(int fd1):QRunnable(),cnnfd{fd1}{
    setAutoDelete(true);

    m_ic = ControllerFactory::getInstance()->createInitController();
    m_mc = ControllerFactory::getInstance()->createMessageController();
    m_pc = ControllerFactory::getInstance()->createPushController();
    m_fc = ControllerFactory::getInstance()->createFriendController();

    m_ic->initDatabase();
    m_ic->createWorkDir();
}

void Task::run()
{
    qDebug()<<"jing ru run le";
    Network network;
    char buf[1024]="";
    int id=0;
    //User user;
    UserProxy userproxy;
    int login = network.recieveMessage(cnnfd, buf);
    auto j1 = nlohmann::json::parse(buf);

    id = j1.at("myid");
    std::cout << "json object id:" << id << "文件描述符" << cnnfd << std::endl;
    userproxy.updateMUsers(id, cnnfd);
    sleep(3);
    while (1) {
        //if(int result=network.Select(cnnfd)){
        int result2 = network.recieveMessage(cnnfd, buf);
        if(result2 == -1){          //套接字关闭或中断,退出while循环，结束线程
            qDebug() << "用户退出" << id;
            userproxy.updateMUsers(id, 0);
            close(cnnfd);
            break;
        }
        else{
            auto j = nlohmann::json::parse(buf);
            std::string request_type = j.at("request_type");
            if(request_type == "recieveuser"){          //从数据库中读取数据（初始化预览界面）

            }
            if(request_type == "recievemsg"){          //从数据库中读取数据（初始化聊天界面）

            }
            if(request_type == "findfriend"){
            }
            if(request_type == "mine"){
            }
            if (request_type == "getfribaseinfo") {
                json fri_info = m_fc->findFriendById(j.at("friendID"));
                network.sendMessage(cnnfd, (fri_info.dump()).data());
            }

            if (request_type == "addfriend") {
                int targetid = j.at("target_id");
                m_fc->storeAddFriendInfo(j.at("my_id"), targetid);
                int target_conn = userproxy.findUserConn(targetid);
                if (target_conn != 0) {
                    network.sendMessage(target_conn, buf);
                }
            }

            if (request_type == "acceptfrinfo") {
                int userid = j.at("acceptor_id");
                int friendid = j.at("requestsender_id");

                int target_conn = userproxy.findUserConn(friendid);
                if (target_conn != 0) {
                    network.sendMessage(target_conn, buf);
                }
                userproxy.updateFriendList(userid, friendid, 1);
            }
            if (request_type == "GetOfflineMessage") {
                std::string userid = j["UserId"];
                // id = j["UserId"];

                std::cout << "reading to read offlinemessage from data" << std::endl;
                std::vector<nlohmann::json> messages = m_mc->pushMessage(std::stoi(userid));
                for (int i = 0; i < messages.size(); i++) {
                    if (messages[i]["MessageType"] == "Text") {
                        messages[i]["request_type"] = "GetOfflineMessage";
                        std::cout << "发送离线消息到服务端" << std::endl;
                        std::cout << messages[i] << std::endl;
                        network.sendMessage(cnnfd, (messages[i].dump()).data());
                    } else {
                        messages[i]["request_type"] = "GetOfflineMessage";
                        network.sendMessage(cnnfd, (messages[i].dump()).data());
                        //读取路径读入程序发送
                        //获取文件转为char并发送
                    }
                }
            }
            if (request_type == "SendMessage") {
                std::cout << "接收到客户端发动消息请求" << std::endl;
                char mediaBuffer[99999] = "";
                std::string temp;
                temp = j["SenderId"];
                std::cout << "SenderId:" << temp << std::endl;
                unsigned int senderid = std::stoi(temp);
                temp = j["ReceiverId"];
                std::cout << "ReceiverId:" << temp << std::endl;
                int receiverid = std::stoi(temp);
                //类型转换有问题
                std::string messageType;
                if (j["MessageType"].is_number()) {
                    messageType = std::to_string(j["MessageType"].get<int>());
                } else if (j["MessageType"].is_string()) {
                    messageType = j["MessageType"].get<std::string>();
                } else {
                    qDebug() << "SenderId is neither number nor string";
                }
                std::string messageContent;
                if (j["MessageContent"].is_number()) {
                    messageContent = std::to_string(j["MessageContent"].get<int>());
                } else if (j["MessageContent"].is_string()) {
                    messageContent = j["MessageContent"].get<std::string>();
                } else {
                    qDebug() << "SenderId is neither number nor string";
                    std::cout << "处理客户端发送的信息:" << std::endl;
                    qDebug() << "SenderId is neither number nor string";
                }
                std::string sendTime;
                if (j["SendTime"].is_number()) {
                    sendTime = std::to_string(j["SendTime"].get<int>());
                } else if (j["SendTime"].is_string()) {
                    sendTime = j["SendTime"].get<std::string>();
                } else {
                    qDebug() << "SenderId is neither number nor string";
                    std::cout << "处理客户端发送的信息:" << std::endl;
                    qDebug() << "SenderId is neither number nor string";
                }

                std::cout << "处理客户端发送的信息:" << std::endl;
                if (messageType == "Vedio" || messageType == "Audio" || messageType == "Picture") {
                    int res = network.recieveMessage(cnnfd, mediaBuffer);
                    std::cout << "多媒体类:" << std::endl;
                    if (res == -1) { //套接字关闭或中断,退出while循环，结束线程
                        userproxy.updateMUsers(id, 0);
                        close(cnnfd);
                        break;
                    }
                }
                int target_conn = userproxy.findUserConn(receiverid);
                if (target_conn != 0) {
                    std::cout << "用户在线直接发送:" << std::endl;
                    if (messageType == "Text") {
                        std::cout << "文本消息类发送:" << std::endl;
                        network.sendMessage(target_conn, buf);
                    } else {
                        network.sendMessage(target_conn, buf);
                        network.sendMessage(target_conn, mediaBuffer);
                    }
                    //传二进制视频再调用一次network.receive
                } else {
                    //存储数据库中
                    if (messageType == "Text") {
                        std::cout << "用户离线存储到数据库中:" << std::endl;
                        m_mc->storeMessageInfo(receiverid,
                                               senderid,
                                               messageContent,
                                               sendTime,
                                               messageType);
                    } else {
                        // 使用数组和长度创建vector
                        std::vector<unsigned char> vec(mediaBuffer,
                                                       mediaBuffer
                                                           + sizeof(mediaBuffer)
                                                                 / sizeof(mediaBuffer[0]));
                        m_mc->storeMessageInfo(receiverid, senderid, vec, sendTime, messageType);
                    }
                }
            }
        }
    }
    qDebug()<<"get out while,the thread will be back to thread pull";

}
