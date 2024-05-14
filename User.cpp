#include "User.h"
#include "UserBroker.h"

std::map<USER_ID, USER_CONN> User::m_users;

User::User() {}

User::User(int user_id)
    : m_user_id(user_id)
{}

User *User::getInfoFromDB() {}

int User::findUserConn(int user_id)
{
    return m_users[user_id];
}

bool User::initializeMUsers()
{
    // find number of all users from DB
    for (int i = 0; i < 10; i++) {
        m_users[i] = 0; // 0 means the user is not connected
    }
    return true;
}

void User::updateMUsers(USER_ID user_id, USER_CONN user_conn)
{
    m_users.insert(std::make_pair(user_id, user_conn));
    // m_users[user_id] = user_conn;
}

void User::updateFriendList(int friend_id, int state)
{
    if (state == 1) {
        m_friendList.push_back(friend_id);
        UserBroker::getInstance()->addFriendRelation(m_user_id, friend_id);
        UserBroker::getInstance()->modifyFriendRequest(m_user_id, friend_id, state);
    } else if (state == -1) {
        auto iter = m_friendList.begin();
        while (iter != m_friendList.end()) {
            if (*iter == friend_id)
                m_friendList.erase(iter);
            else
                iter++;
        }
    }
}
