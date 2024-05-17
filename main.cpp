#include "network.h"
#include "message.h"
#include <QDebug>
#include <sys/ioctl.h>
#include <nlohmann/json.hpp>
#include <iostream>
int main(int argc, char *argv[])
{
    Network network;
    network.createSocket();//

    int cnnfd=network.acceptSocket();
    int cnnfd2=network.acceptSocket();

    char buf[1024]="";
    while(1){
        if(int result=network.Select(cnnfd)){
            qDebug()<<"zheshijieguo  cnnfd:"<<result;
            network.recieveMessage(cnnfd,buf);
            network.sendMessage(cnnfd2,buf);
            auto j=nlohmann::json::parse(buf);
            std::cout<<"jso bj:"<<j.at("id")<<std::endl;
        }
        if(int re=network.Select(cnnfd2)){
            qDebug()<<"zheshijieguo  cnnfd2:"<<re;
            network.recieveMessage(cnnfd2,buf);
            network.sendMessage(cnnfd,buf);
            auto j=nlohmann::json::parse(buf);
            std::cout<<"jso bj:"<<j.at("id")<<std::endl;
        }
    }
}
