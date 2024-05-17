//#include<QDebug> must put forward,why?
#include <QDebug>
#include "network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "string.h"
#include <sys/ioctl.h>
//#include <sys/ioctl.h>

#define BUF_SIZE  1024
#define PORT 9879
Network::Network() {}

void Network::createSocket()
{
    m_listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl((u_int32_t)0x00000000);
    servaddr.sin_port = htons(PORT);    //9878
    if(bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
        qDebug()<<"bind socket erro!";
    else {
        qDebug()<<"bind succeed!";
    }

    if(listen(m_listenfd,1000) < 0)
        qDebug()<<"listen socket erro!";
    else {
        qDebug()<<"listen succeed!";
    }

}

int Network::acceptSocket()
{
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int cnnfd = accept(m_listenfd, (struct sockaddr *)&cliaddr,&clilen);
    if(cnnfd < 0){
        qDebug()<<"Accept socket failed. Errorn info";
    }
    else {
        qDebug()<<"Accept succeed Client port:"<<cliaddr.sin_port;
    }
    return cnnfd;
}

void Network::recieveMessage(int cnnfd,char* buf)
{
    int size=0;
    read(cnnfd,&size,sizeof(size));
    int n{0};
    int offset{0};
    memset(buf,'\0',BUF_SIZE);
    while ((size-n)>0) {
        n=read(cnnfd,buf+offset,1024);
        offset=offset+n;
        if(n<0)
            qDebug()<<"faild to read message from connect socket!";
        else {
            qDebug()<<"n:"<<n;
            qDebug()<<"succeed to reade msg from cnnfd :"<<buf;
        }
    }
}

void Network::sendMessage(int cnnfd,char* buf)
{
    int size=strlen(buf);
    write(cnnfd,&size,sizeof(size));
    qDebug()<<"network.cpp sndmsg buf.len:"<<size;
    int n=0;
    int offset=0;
    while ((size-n)>0) {
        n=write(cnnfd,buf+offset,size);
        offset=offset+n;
        if(n<0)
            qDebug()<<"failed to write msg to connfd socket!";
        else
            qDebug()<<"write to socket succeed!n="<<n<<"   msg:"<<buf;
    }
}

int Network::Select(int cnnfd)
{
    fd_set fdreads;
    struct timeval tv;
    int retval;

    FD_ZERO(&fdreads);
    FD_SET(cnnfd,&fdreads);

    tv.tv_sec=2;
    tv.tv_usec=0;

    retval = select(cnnfd+1,&fdreads,NULL,NULL,&tv);
    if(retval >0 &&FD_ISSET(cnnfd,&fdreads) )
        return 1;
    else {
        return 0;
    }
}

