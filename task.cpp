#include "task.h"
#include "network.h"
#include "user.h"
#include "userproxy.h"
#include <QDebug>
#include <nlohmann/json.hpp>
#include <iostream>

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
    while (1) {                     //
        //if(int result=network.Select(cnnfd)){
            //qDebug()<<"zheshijieguo  cnnfd:"<<result;

        int result2=network.recieveMessage(cnnfd,buf);
        if(result2 == -1){          //套接字关闭或中断,退出while循环，结束线程
            userproxy.updateMUsers(id,0);
            close(cnnfd);
            break;
        }
        else{
            auto j=nlohmann::json::parse(buf);

            id=j.at("myid");
            std::cout<<"json object id:"<<id<<std::endl;

            int acid=j.at("acceptid");
            std::cout<<"json object acceptid:"<<acid<<std::endl;

            std::string request_type=j.at("request_type");
            std::cout<<"json object request:"<<request_type<<std::endl;

            userproxy.updateMUsers(id,cnnfd);       //用id和已连接描述符更新容器   但是这样每次都要重新赋值会不会浪费资源，且考虑加锁

            if(request_type == "sendmsg")
            {
                qDebug()<<"sleep 10s";
                sleep(30);                       //可删，防止测试时,时间太短另外一个用户还没连上加入到容器中
                qDebug()<<"sleep over";
                int cnnfd2=userproxy.findUserConn(acid);   //通过接受者id查找已连接描述符

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
        }
    }
    qDebug()<<"get out while,the thread will be back to thread pull";

}
