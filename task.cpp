#include "task.h"
#include <QDebug>
#include "network.h"
#include "user.h"
#include "userproxy.h"
#include <iostream>
#include <nlohmann/json.hpp>

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
    auto j = nlohmann::json::parse(buf);

    id = j.at("myid");
    userproxy.updateMUsers(id, cnnfd);
    //用id和已连接描述符更新容器   但是这样每次都要重新赋值会不会浪费资源，且考虑加锁

    while (1) { //
        //if(int result=network.Select(cnnfd)){
            //qDebug()<<"zheshijieguo  cnnfd:"<<result;

        int result2=network.recieveMessage(cnnfd,buf);
        if(result2 == -1){          //套接字关闭或中断,退出while循环，结束线程
            userproxy.updateMUsers(id,0);
            close(cnnfd);
            break;
        }
        else{
            auto j = nlohmann::json::parse(buf);

            id = j.at("myid");
            qDebug() << "cnnfd " << cnnfd;
            std::string request_type = j.at("request_type");
            std::cout << "json object id:" << id << std::endl;
            std::cout << "json object request:" << request_type << std::endl;

            if (request_type == "sendmsg") {
                // qDebug()<<"sleep 10s";
                // sleep(30);                       //可删，防止测试时,时间太短另外一个用户还没连上加入到容器中
                // qDebug()<<"sleep over";

                int acid = j.at("acceptid");
                std::cout << "json object acceptid:" << acid << std::endl;

                int cnnfd2 = userproxy.findUserConn(acid); //通过接受者id查找已连接描述符

                std::string content;
                content=j.at("content");

                if(cnnfd2==0){
                    qDebug()<<"can't find cnnfd2!";    //从这里续写如果接收端不在线，将数据存入数据库
                }
                else{
                    network.sendMessage(cnnfd2,buf);
                }
            }
            if(request_type == "recieveuser"){          //从数据库中读取数据（初始化预览界面）

            }
            if(request_type == "recievemsg"){          //从数据库中读取数据（初始化聊天界面）

            }
            if(request_type == "findfriend"){
            }
            if(request_type == "mine"){
            }

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
            qDebug() << "finished a loop";
        }
    }
    qDebug()<<"get out while,the thread will be back to thread pull";

}
