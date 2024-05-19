#ifndef NETWORK_H
#define NETWORK_H

#define MAX 1028
class Network
{
public:
    Network();
    void createSocket();
    int acceptSocket();

    int recieveMessage(int cnnfd,char* buf);
    void sendMessage(int cnnfd,char*);
    int Select(int cnnfd);
private:
    int m_listenfd;
    //char buf[MAX];
    //int m_cnnfd;
};

#endif // NETWORK_H
