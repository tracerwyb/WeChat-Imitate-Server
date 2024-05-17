#include "network.h"
#include "message.h"
#include "server.h"
#include <QDebug>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    Network network;
    network.createSocket();//
    Server server;

    int cnnfd=network.acceptSocket();
    int cnnfd2=network.acceptSocket();

    char buf[1024]="";
    while(1){
        if(int result=network.Select(cnnfd)){
            qDebug()<<"zheshijieguo  cnnfd:"<<result;
            network.recieveMessage(cnnfd,buf);
            network.sendMessage(cnnfd2,buf);
            server.conversionJson(buf);  //this conversion turn json_string to json object,infact just a row,when you understand please change or delete it.
        }
        if(int re=network.Select(cnnfd2)){
            qDebug()<<"zheshijieguo  cnnfd2:"<<re;
            network.recieveMessage(cnnfd2,buf);
            network.sendMessage(cnnfd,buf);
            server.conversionJson(buf);

        }
    }

}
