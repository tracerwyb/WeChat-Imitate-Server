#ifndef SERVER_H
#define SERVER_H

//#include "threadpool.h"

class Server
{
private:
//    ThreadPool m_threadPool;

public:
    Server();
    void start();
    void processClientRequest(int &fd);
    bool receive();
    void send();
};

#endif
