#include "message.h"
#include <string.h>

Message::Message()
{}

void Message::SendMessage(int receive)
{
    int n=strlen(m_msg);
    network.sendMessage(receive,m_msg,n);
}

void Message::RecieveMessage(int send,int size)
{
    network.recieveMessage(send,m_msg,size);
}
