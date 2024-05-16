#include "message.h"
#include <string.h>

Message::Message()
{}

void Message::SendMessage(int receive)
{
    network.sendMessage(receive,m_msg);
}

void Message::RecieveMessage(int send)
{
    network.recieveMessage(send,m_msg);
}
