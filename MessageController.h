#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include "Controller.h"

class MessageController : public Controller
{
public:
    static MessageController *getInstance();
    ~MessageController();

    void storeMessageInfo();
	void pushMessage();

private:
    static MessageController *m_msgController;
    MessageController();
};

#endif
