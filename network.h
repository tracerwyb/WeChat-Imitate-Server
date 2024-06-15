#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#define MAX 1028
class Network
{
public:
    Network();
    void createSocket();
    int acceptSocket();

    int recieveMessage(int cnnfd,char* buf);
    void sendMessage(int cnnfd,char*);

    //离线
    void sendImage(int cnnfd,std::string path);
    //在线
    void sendImage(int cnnfd,char *buf,long buf_len);

    long recImage(int cnnfd,char *filebuf);
    int Select(int cnnfd);
private:
    int m_listenfd;
    //char buf[MAX];
    //int m_cnnfd;
};

#endif // NETWORK_H
