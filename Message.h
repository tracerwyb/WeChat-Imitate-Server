#ifndef MESSAGE_H
#define MESSAGE_H

namespace entity {
	class Message : FrameworkDesign::MessageInterface {

	private:
		FrameworkDesign::MessageProxy message;
		unsigned int receiverid;
		unsigned int senderid;
		string type;
		string content;
		DateTime dateTime;

	public:
		json processMessage();
	};
}

#endif
