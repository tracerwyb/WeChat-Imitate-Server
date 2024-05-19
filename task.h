#ifndef TASK_H
#define TASK_H
#include <QThreadPool>
class Task:public QRunnable
{
private:
    int cnnfd;
    //int cnnfd2;
public:
    explicit Task(int fd1);
    //~Task();
    void run()override;
};

#endif // TASK_H
