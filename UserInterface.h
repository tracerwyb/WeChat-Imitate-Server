#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#define USER_ID unsigned int
#define USER_CONN int

class User;

class UserInterface {
public:
    virtual void modifyBaseInfo(){};
    virtual void logOff(){};
    virtual User *findFriendByID(int friend_id) { return nullptr; };
    virtual User *getInfoFromDB() { return nullptr; };
    virtual void updateFriendList(int user_id, int friend_id, int state){};
    virtual void updateFriendList(int friend_id, int state){};
};

#endif
