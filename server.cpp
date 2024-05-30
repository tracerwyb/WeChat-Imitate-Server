 #include "server.h"
#include "task.h"
#include "message.h"
#include "network.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <QThreadPool>
#include <QDebug>
#define ADDFRIEND 1
#define DELETEFRIEND -1
#define BUF_SIZE 1024

Server::Server()
{
  //  ThreadPool m_threadPool;
    /*InitController *m_ic;
    MessageController *m_mc;
    PushController *m_pc;
    FriendController *m_fc;
    m_ic = ControllerFactory::getInstance()->createInitController();
    m_mc = ControllerFactory::getInstance()->createMessageController();
    m_pc = ControllerFactory::getInstance()->createPushController();
    m_fc = ControllerFactory::getInstance()->createFriendController();

    m_ic->initDatabase();
    m_ic->createWorkDir();
*/

    //Network network;
    //network.createSocket(); //

    // // ------------------------------------------------------------------------------------------
    // int user_id, friend_id;
    // user_id = 20412785;
    // friend_id = 20209834;

    // int cnnfd = network.acceptSocket();
    // int cnnfd2 = network.acceptSocket();

    // if (cnnfd) {
    //     m_ic->recordUserConn(user_id, cnnfd);
    // }
    // if (cnnfd2) {
    //     m_ic->recordUserConn(friend_id, cnnfd2);
    // }
    // char msg1[BUF_SIZE];
    // char msg2[BUF_SIZE];

    // while (1) {
    //     if (int result = network.Select(cnnfd)) {
    //         qDebug() << "zheshijieguo  cnnfd:" << result;
    //         int nbytes;
    //         if (ioctl(cnnfd, FIONREAD, &nbytes) == -1) {
    //             qDebug() << "erro iotrl";
    //         } else {
    //             if (nbytes > 0) {
    //                 qDebug() << "buffer have data:" << nbytes;
    //             } else {
    //                 qDebug() << "no data";
    //             }
    //         }
    //         network.recieveMessage(cnnfd, msg1);
    //         m_fc->updateFriendList(user_id, friend_id, ADDFRIEND);
    //         network.sendMessage(cnnfd2, msg1, strlen(msg1));
    //     }
    //     if (int re = network.Select(cnnfd2)) {
    //         qDebug() << "zheshijieguo  cnnfd2:" << re;
    //         int nbytes;
    //         if (ioctl(cnnfd, FIONREAD, &nbytes) == -1) {
    //             qDebug() << "erro iotrl";
    //         } else {
    //             if (nbytes > 0) {
    //                 qDebug() << "buffer have data:" << nbytes;
    //             } else {
    //                 qDebug() << "no data";
    //             }
    //         }
    //         network.recieveMessage(cnnfd2, msg2);
    //         network.sendMessage(cnnfd, msg2, strlen(msg2));
    //     }
    // }

    // // --------------------------------------------------------------------------------------------------

    // test

    // if client search a person by id

    // std::cout << m_fc->findFriendById(friend_id); // User*

    // get that person infomation
    // User user;
    // m_pc->pushMessage(user.getInfoFromDB(), user.findUserConn(friend_id));
    // pretend server has received message(add friend request) from client (message with user_id and friend_id)
    // m_fc->pushAddFriendRequest(user_id, friend_id);
    // m_fc->storeAddFriendInfo(user_id, friend_id);

    // if friend accept friend_request: update db sheet FriendRequest and Relation
    // m_fc->updateFriendList(user_id, friend_id, DELETEFRIEND);
}
void Server::start()
{
    Network network;
    network.createSocket();//

    QThreadPool::globalInstance()->setMaxThreadCount(50);

    while(1){
        int cnnfd=network.acceptSocket();
        Task* ts=new Task(cnnfd); //传入连接套接字描述符，任务函数读取这条消息，找到接收者id并查找套接字描述符转发
        QThreadPool::globalInstance()->start(ts);  //将请求放入线程池的任务队列中，等待线程执行
    }
}
void Server::processClientRequest(int &fd) {}

bool Server::receive() {return true;}

void Server::send() {}



