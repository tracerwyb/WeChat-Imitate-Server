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

    void sendImage(int cnnfd,std::string path);
    void sendImage(int cnnfd,char *buf,long buf_len);

    long recImage(int cnnfd,char *filebuf);
    int Select(int cnnfd);
private:
    int m_listenfd;
    //char buf[MAX];
    //int m_cnnfd;
};

#endif // NETWORK_H
