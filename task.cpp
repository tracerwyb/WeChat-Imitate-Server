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
    char buf[102400]="";
    int id=0;
    //User user;

    UserProxy userproxy;

    int login=network.recieveMessage(cnnfd,buf);
    auto j1 = nlohmann::json::parse(buf);
    id=j1.at("myid");
    std::cout<<"json object id:"<<id<<std::endl;
    userproxy.updateMUsers(id,cnnfd);       //用id和已连接描述符更新容器   但是这样每次都要重新赋值会不会浪费资源，且考虑加锁

    while (1) {                     //
        //if(int result=network.Select(cnnfd)){
            //qDebug()<<"zheshijieguo  cnnfd:"<<result;
        std::cout << "json object id:" << id << "文件描述符" << cnnfd << std::endl;
        int result2=network.recieveMessage(cnnfd,buf);
        if(result2 == -1){          //套接字关闭或中断,退出while循环，结束线程
            qDebug() << "用户退出" << id;
            userproxy.updateMUsers(id, 0);
            close(cnnfd);
            break;
        }
        else{
            auto j = nlohmann::json::parse(buf);
            qDebug() << "cnnfd " << cnnfd;
            std::string request_type = j.at("request_type");
            std::cout << "json object id:" << id << std::endl;
            std::cout << "json object request:" << request_type << std::endl;

            // userproxy.updateMUsers(id,cnnfd);       //用id和已连接描述符更新容器   但是这样每次都要重新赋值会不会浪费资源，且考虑加锁
//----------
            if(request_type == "sendimage")
            {
                // id=j.at("myid");
                // std::cout<<"json object id:"<<id<<std::endl;

                int acid=j.at("acceptid");
                std::cout<<"json object acceptid:"<<acid<<std::endl;

                int cnnfd2=userproxy.findUserConn(acid);   //通过接受者id查找已连接描述符

                char filebuf[204800]="";
                long filebuf_len=network.recImage(cnnfd,filebuf);

                if(cnnfd2==0){
                    qDebug()<<"can't find cnnfd2!";    //从这里续写如果接收端不在线，将数据存入数据库
                }
                else{
                    network.sendMessage(cnnfd2,buf);
                    network.sendImage(cnnfd2,filebuf,filebuf_len);
                }
            }
            //-----------
            if (request_type == "initPersonalPage") {
                nlohmann::json j;
                j["request_type"]
                    = "initPersonalPage"; //发送很多张图片，通过for循环，1张图片要发送两次，一次是图片信息，一次是图片的内容
                j["imageName"] = "avater";
                std::string s = j.dump();
                network.sendMessage(cnnfd, s.data());
                std::string path = "/run/media/root/study/avater1.jpg";
                network.sendImage(cnnfd, path);
                //用户账号id和头像
            }
            //-----------
            if (request_type == "initUsersAvatar") {
                nlohmann::json json_array = nlohmann::json::array();
                std::string userid = j["UserId"];
                json_array = PushController::getInstance()->pushUserAvatar(std::stoi(userid));
                //发回用户账号id和头像
                for (auto &obj : json_array) {
                    std::string s = obj.dump();
                    std::cout << "发送头像图片: " << s << std::endl;
                    network.sendMessage(cnnfd, s.data());
                    network.sendImage(cnnfd, obj.at("UserAvatar"));
                }
            }
            if (request_type == "initFriendInfo") {
                nlohmann::json json_array = nlohmann::json::array();
                std::string userid = j["UserId"];
                json_array = PushController::getInstance()->pushUserFriendsInfo(std::stoi(userid));
                //发回用户账号id和头像
                for (auto &obj : json_array) {
                    std::string s = obj.dump();
                    std::cout << "发送好友信息" << s << std::endl;
                    network.sendMessage(cnnfd, s.data());
                }
            }
            //-----------------
            if (request_type == "isfriend") {
                // qDebug() << buf;
                int friendid = j.at("friendID");

                // qDebug() << "friend_id: " << std::stoi(friendid);
                json isfriend = m_fc->isFriend(id, friendid);
                qDebug() << "isfriend_task: " << isfriend.dump();
                network.sendMessage(cnnfd, (isfriend.dump()).data());
            }

            if (request_type == "getfribaseinfo") {
                int friendid = j.at("friendID");
                json fri_info = m_fc->findFriendById(friendid);
                qDebug() << "friend info: " << fri_info.dump();
                if (fri_info != NULL) {
                    network.sendMessage(cnnfd, (fri_info.dump()).data());
                }
            }

            if (request_type == "addfriend") {
                qDebug() << "entered server addfriend";
                int targetid = j.at("target_id");
                m_fc->storeAddFriendInfo(j.at("myid"), targetid);
                int target_conn = userproxy.findUserConn(targetid);
                qDebug() << "target_conn: " << target_conn;
                qDebug() << "my_conn: " << userproxy.findUserConn(id);
                if (target_conn != 0) {
                    network.sendMessage(target_conn, buf);
                }
            }

            if (request_type == "acceptfrinfo") {
                int userid = j.at("myid");
                int friendid = j.at("requestsender_id");

                int target_conn = userproxy.findUserConn(friendid);
                if (target_conn != 0) {
                    network.sendMessage(target_conn, buf);
                }
                userproxy.updateFriendList(id, friendid, 1);
            }

            if (request_type == "GetOfflineMessage") {
                std::string userid = j["UserId"];
                std::vector<nlohmann::json> messages = m_mc->pushMessage(std::stoi(userid));
                for (int i = 0; i < messages.size(); i++) {
                    if (messages[i]["MessageType"] == "Text") {
                        messages[i]["request_type"] = "GetOfflineMessage";
                        std::cout << "发送离线消息到服务端:" << messages[i] << std::endl;
                        network.sendMessage(cnnfd, (messages[i].dump()).data());
                    } else {
                        messages[i]["request_type"] = "GetOfflineMessage";
                        network.sendMessage(cnnfd, (messages[i].dump()).data());
                        network.sendImage(cnnfd, messages[i]["MessageContent"]);
                        //读取路径读入程序发送
                        //获取文件转为char并发送
                    }
                }
            }
            if (request_type == "SendMessage") {
                std::cout << "接收到客户端发动消息请求" << std::endl;
                char filebuf[504800] = "";
                long filebuf_len;

                std::string temp;
                temp = j["SenderId"];
                std::cout << "SenderId:" << temp << std::endl;
                unsigned int senderid = std::stoi(temp);
                temp = j["ReceiverId"];
                std::cout << "ReceiverId:" << temp << std::endl;
                int receiverid = std::stoi(temp);
                //类型转换有问题

                std::string messageType = j.at("MessageType");
                std::string messageContent = j.at("MessageContent");
                std::string sendTime = j.at("SendTime");

                std::cout << "处理客户端发送的信息:" << std::endl;
                if (messageType == "Vedio" || messageType == "Audio" || messageType == "Picture") {
                    std::cout << "多媒体类:" << std::endl;
                    filebuf_len = network.recImage(cnnfd, filebuf);
                }

                int target_conn = userproxy.findUserConn(receiverid);
                if (target_conn != 0) {
                    std::cout << "用户在线直接发送:" << std::endl;
                    if (messageType == "Text") {
                        std::cout << "文本消息类发送:" << std::endl;
                        network.sendMessage(target_conn, buf);
                    } else {
                        network.sendMessage(target_conn, buf);
                        network.sendImage(target_conn, filebuf, filebuf_len);
                        //666
                    }
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
                        std::vector<unsigned char> vec(filebuf,
                                                       filebuf
                                                           + sizeof(filebuf) / sizeof(filebuf[0]));
                        m_mc->storeMessageInfo(receiverid, senderid, vec, sendTime, messageType);
                    }
                }
            }
        }
    }
    qDebug()<<"get out while,the thread will be back to thread pull";

}
