#ifndef USER_H
#define USER_H

#include "userinterface.h"
#include <map>
#include <vector>

#define USER_ID unsigned int
#define USER_CONN int
#define REQUEST_STATE int //-1 0 1: refuse, no response, agree

class User : public UserInterface
{
private:
    USER_ID m_user_id;
    // std::string m_nickname;
    // std::string avatar_path;
    // std::string m_gender;
    // std::string m_area;
    // std::string m_singnature;
    std::vector<unsigned int> m_friendList;
    std::vector<std::map<USER_ID, REQUEST_STATE>> m_friendRequest;
    static std::map<USER_ID, USER_CONN> m_users; // contain all users in DB

public:
    User();
    User(int user_id);
    json getInfoFromDB();
    json toJson();
    bool isFriend(int friend_id);
    void initFriendList();
    void updateFriendList(int friend_id, int state); // state: type of operation to friend
    static int findUserConn(int user_id);
    static bool initializeMUsers(); // initialize m_users
    static void updateMUsers(USER_ID user_id, USER_CONN user_conn);
};

#endif // USER_H
