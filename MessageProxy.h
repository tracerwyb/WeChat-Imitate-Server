#ifndef MESSAGEPROXY_H
#define MESSAGEPROXY_H

namespace FrameworkDesign {
	class MessageProxy : FrameworkDesign::MessageInterface {

	public:
		vector<entity::Message> m_msgSequence;

		json sendMessage();

		void deleteMsg();
	};
}

#endif
