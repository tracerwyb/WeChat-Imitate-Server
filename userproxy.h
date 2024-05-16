#ifndef USERPROXY_H
#define USERPROXY_H
#include "userinterface.h"
class UserInterface;
class UserProxy : UserInterface {


public:
	void modifyBaseInfo();

	void addFriend();

	void deleteFriend();

	void logOff();
};

#endif
