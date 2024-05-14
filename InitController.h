#ifndef INITCONTROLLER_H
#define INITCONTROLLER_H

#include "Controller.h"

class InitController : public Controller
{
public:
    static InitController *getInstance();
    ~InitController();

private:
    static InitController *m_initController;
    InitController();
};

#endif
