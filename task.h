#ifndef TASK_H
#define TASK_H
#include <QThreadPool>
#include "initcontroller.h"
#include "messagecontroller.h"
#include "pushcontroller.h"
#include "friendcontroller.h"
#include "controllerfactory.h"
class Task:public QRunnable
{
private:
    int cnnfd;
    InitController *m_ic;
    MessageController *m_mc;
    PushController *m_pc;
    FriendController *m_fc;
    ControllerFactory *m_controllerFactory;
    //int cnnfd2

public:
    explicit Task(int fd1);
    //~Task();
    void run()override;

};

#endif // TASK_H
