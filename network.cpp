//#include<QDebug> must put forward,why?
#include <QDebug>
#include "network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fstream>
//#include <sys/ioctl.h>

#define BUF_SIZE  1024
#define PORT 9878
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
        qDebug() << "Accept succeed Client port:" << cliaddr.sin_port;
    }
    return cnnfd;
}



int Network::recieveMessage(int cnnfd,char* buf)
{
    int size=0;
    int readbyte=read(cnnfd,&size,sizeof(size));
    qDebug() << "read size :" << size;
    if(readbyte<=0){   //套接字关闭或中断
        return -1;
    }
    else {
        int n{0};
        int offset{0};
        memset(buf,'\0',BUF_SIZE);
        while ((size-n)>0) {
            n=read(cnnfd,buf+offset,size);
            offset=offset+n;
            if(n<0){
                qDebug()<<"faild to read message from connect socket!";
                break;
            }
            else {
                qDebug()<<"n:"<<n;
                qDebug()<<"succeed to reade msg from cnnfd :"<<buf;
            }
        }
    }
    return 0;
}

void Network::sendMessage(int cnnfd,char* buf)
{
    int size=strlen(buf);
    write(cnnfd,&size,sizeof(size));
    qDebug()<<"network.cpp sndmsg buf.len:"<<size;
    int n=0;
    int offset = 0;
    qDebug() << "文件描述符：" << cnnfd;
    while ((size-n)>0) {
        n=write(cnnfd,buf+offset,size);
        offset=offset+n;
        if(n<0){
            fprintf(stderr, "recv failed: %s\n", strerror(errno));
            qDebug()<<"failed to write msg to connfd socket!";
            break;
        }
        else
            qDebug()<<"write to socket succeed!n="<<n<<"   msg:"<<buf;
    }
}

void Network::sendImage(int cnnfd, std::string path)
{
    std::ifstream file("/root/WeChat-Imitate-Client/" + path, std::ios::binary | std::ios::ate);
    if(!file)
        qDebug()<<"file open erro!";

    std::streamsize size=file.tellg();
    qDebug()<<"file size:"<<size;
    qDebug()<<"sizeof(size):"<<sizeof(size);

    write(cnnfd,&size,sizeof(size));
    file.seekg(0,std::ios::beg);

    char buf[10240];

    while (size>0) {
        std::streamsize file_read=file.read(buf,sizeof(buf)).gcount();
        qDebug()<<"file_read:"<<file_read;
        write(cnnfd,buf,file_read);
        size=size-file_read;
    }
}

void Network::sendImage(int cnnfd, char* buf,long buf_len)
{
    // std::ifstream file(path,std::ios::binary|std::ios::ate);
    // if(!file)
    //     qDebug()<<"file open erro!";

    // std::streamsize size=file.tellg();
    long size;
    size=buf_len;

    qDebug()<<"file size:"<<size;
    qDebug()<<"sizeof(size):"<<sizeof(size);

    write(cnnfd,&size,sizeof(long));
    // file.seekg(0,std::ios::beg);

    // char buf[10240];

    while (size>0) {
        // std::streamsize file_read=file.read(buf,sizeof(buf)).gcount();
        int n_write=write(cnnfd,buf,size);
        qDebug()<<"write_buf:"<<n_write;
        size=size-n_write;
    }
}

long Network::recImage(int cnnfd, char *filebuf)
{
    // char filebuf[202400]="";
    int n_read;
    long posx = 0;
    int size;
    if ((read(cnnfd, &size, 8)) <= 0) { //读取消息长度
        qDebug() << "read image length erro";
    }
    qDebug() << "!!!!!:" << size;

    while (size > 0) {
        n_read = read(cnnfd, filebuf + posx, 102400); //

        qDebug() << "n_read:" << n_read;
        if (n_read == 0) {
            qDebug() << "recimg erro,maybe socket was closed!";
            break;
        }
        size = size - n_read;
        posx = posx + n_read;
    }
    qDebug() << "rec image filebuf length:" << strlen(filebuf);
    return posx;
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

