#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network
{
private:
    int m_listenFd;

public:
    int createSocket();

    int bindSocket();

    int listenSocket();

    int acceptSocket();

    void closeSocket();

    int pollSocket();

    void sendMessage(int conn, char *buf);

    void receiveMessage(char *buffer);

    int sendFile(std::string path);
};

#endif
