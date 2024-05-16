#ifndef USER_H
#define USER_H

#include "userinterface.h"
#include <string>
#include <vector>

class User : public UserInterface
{
private:
    unsigned int m_user_id;
    std::string m_nickname;
    std::string avatar_path;
    std::string m_gender;
    std::string m_area;
    std::string m_singnature;
    std::vector<unsigned int> firendList;

public:
    User();
    User getInfoFromDB();
};

#endif // USER_H
