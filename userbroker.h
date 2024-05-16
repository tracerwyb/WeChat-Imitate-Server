#ifndef USERBROKER_H
#define USERBROKER_H
#include "relationalbroker.h"

class RationBroker;

class UserBroker : RelationalBroker
{
public:
	static UserBroker* m_userBroker;

	static UserBroker* getInstance();

	void findFriend();

	bool storeFriendRequest();

	int modifyFriendRequest();

	bool addFriendRelation();

	bool deleteFriendRelation();

	bool logOffUser();

	bool modifyUserInfo();
};

#endif
