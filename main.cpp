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
    }
}
