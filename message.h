#ifndef MESSAGE_H
#define MESSAGE_H

#include "network.h"
#define BUF_SIZE 1024
class Message
{
public:
    Message();
    void SendMessage(int receive);
    void RecieveMessage(int send,int size);
private:
    Network network;
    char m_msg[BUF_SIZE];
};

#endif // MESSAGE_H
