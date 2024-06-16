#include "user.h"
#include <QDebug>
#include "userbroker.h"

std::map<USER_ID, USER_CONN> User::m_users;

User::User() {}

User::User(int user_id)
    : m_user_id(user_id)
{}

json User::getInfoFromDB()
{
    return UserBroker::getInstance()->findUser(m_user_id);
}

int User::findUserConn(int user_id)
{
    qDebug() << m_users;
    return m_users[user_id];
}

bool User::isFriend(int friend_id)
{
    return UserBroker::getInstance()->isFriend(m_user_id, friend_id);
}

json User::toJson()
{
    json user;

    user["UserID"] = m_user_id;
    // user["U_Nickname"] = m_nickname;
    // user["U_Avater"] = avatar_path;
    // user["U_Gender"] = m_gender;
    // user["U_Area"] = m_area;
    // user["U_Signature"] = m_singnature;

    return user;
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
    // m_users.insert(std::make_pair(user_id, user_conn));
    m_users[user_id] = user_conn; // 插入新值
    qDebug() << m_users;
    qDebug() << m_users[user_id];
    // m_users[user_id] = user_conn;
}

void User::updateFriendList(int friend_id, int state)
{
    if (state == 1) {
        m_friendList.push_back(friend_id);
        UserBroker::getInstance()->addFriendRelation(m_user_id, friend_id);
    } else if (state == -1) {
        UserBroker::getInstance()->deleteFriendRelation(m_user_id, friend_id);
        auto iter = m_friendList.begin();
        while (iter != m_friendList.end()) {
            if (*iter == friend_id)
                m_friendList.erase(iter);
            else
                iter++;
        }
    }
}
