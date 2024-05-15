#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#define USER_ID unsigned int
#define USER_CONN int

#include "nlohmann/json.hpp"

using nlohmann::json;

class User;

class UserInterface {
public:
    virtual void modifyBaseInfo(){};
    virtual void logOff(){};
    virtual json findFriendByID(int friend_id) { return nullptr; };
    virtual json getInfoFromDB() { return nullptr; };
    virtual void updateFriendList(int user_id, int friend_id, int state){};
    virtual void updateFriendList(int friend_id, int state){};
};

#endif
