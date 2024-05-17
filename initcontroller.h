#ifndef INITCONTROLLER_H
#define INITCONTROLLER_H

#include "controller.h"

class InitController : public Controller
{
public:
    static InitController *getInstance();
    void createWorkDir();
    void recordUserConn(USER_ID user_id, USER_CONN user_conn);
    void initDatabase();
    void initWhenConn(); // initialize all operation while user get connect socket
    ~InitController();

private:
    static InitController *m_initController;
    InitController();
};

#endif
