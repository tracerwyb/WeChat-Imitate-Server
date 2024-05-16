#include "network.h"
#include "message.h"
#include <QDebug>
#include <sys/ioctl.h>

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
            msg1.RecieveMessage(cnnfd);
            msg1.SendMessage(cnnfd2);
        }
        if(int re=network.Select(cnnfd2)){
            qDebug()<<"zheshijieguo  cnnfd2:"<<re;
            msg2.RecieveMessage(cnnfd2);
            msg2.SendMessage(cnnfd);
        }
    }

    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
