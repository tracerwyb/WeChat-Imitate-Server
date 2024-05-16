#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H
#include "controller.h"

class FriendController : Controller {


public:
	void findFriendById();

	void storeAddFriendInfo();

	void pushAddFriendRequest();

	void updateFriendList();

	void newFriend();
};

#endif
