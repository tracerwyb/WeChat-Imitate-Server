#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

namespace FrameworkDesign {
	class MessageBroker : FrameworkDesign::RelationalBroker {

	public:
		static MessageBroker* m_msgBroker;

		static MessageBroker* getInstance();

		bool addNewMessage();

		bool delMsgForUser();

		bool deleteMessage();
	};
}

#endif
