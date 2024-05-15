#ifndef NETWORK_H
#define NETWORK_H

#define MAX 1028
class Network
{
public:
    Network();
    void createSocket();
    int acceptSocket();
    void recieveMessage(int cnnfd,char* buf,int size);
    void sendMessage(int cnnfd,char* ,int size);
    int Select(int cnnfd);
private:
    int m_listenfd;
    //char buf[MAX];
    //int m_cnnfd;
};

#endif // NETWORK_H
