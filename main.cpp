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
/*
#include "network.h"
#include "message.h"
#include <sys/ioctl.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    Network network;
    network.createSocket();//

    int cnnfd=network.acceptSocket();
    int cnnfd2=network.acceptSocket();

    Message msg1;
    Message msg2;

    while(1){
        if(int result=network.Select(cnnfd)){
            qDebug()<<"zheshijieguo  cnnfd:"<<result;
            int nbytes;
            if(ioctl(cnnfd,FIONREAD,&nbytes) == -1){
                qDebug()<<"erro iotrl";
            }else{
                if(nbytes>0){
                    qDebug()<<"buffer have data:"<<nbytes;
                }
                else {
                    qDebug()<<"no data";
                }
            }
            msg1.RecieveMessage(cnnfd,nbytes);
            msg1.SendMessage(cnnfd2);
        }
        if(int re=network.Select(cnnfd2)){
            qDebug()<<"zheshijieguo  cnnfd2:"<<re;
            int nbytes;
            if(ioctl(cnnfd,FIONREAD,&nbytes) == -1){
                qDebug()<<"erro iotrl";
            }else{
                if(nbytes>0){
                    qDebug()<<"buffer have data:"<<nbytes;
                }
                else {
                    qDebug()<<"no data";
                }
            }
            msg2.RecieveMessage(cnnfd2,nbytes);
            msg2.SendMessage(cnnfd);
        }
    }*/
}
