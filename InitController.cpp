#include "InitController.h"

InitController *InitController::m_initController;

InitController::InitController() {}

InitController *InitController::getInstance()
{
    if (m_initController == nullptr) {
        m_initController = new InitController();
    }
    return m_initController;
}
