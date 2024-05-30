#ifndef TASK_H
#define TASK_H
#include <QThreadPool>
#include "controllerfactory.h"

class InitController;
class MessageController;
class PushController;
class FriendController;

class Task:public QRunnable
{
private:
    int cnnfd;
    //int cnnfd2;
    InitController *m_ic;
    MessageController *m_mc;
    PushController *m_pc;
    FriendController *m_fc;
    ControllerFactory *m_controllerFactory;

public:
    explicit Task(int fd1);
    //~Task();
    void run()override;
};

#endif // TASK_H
