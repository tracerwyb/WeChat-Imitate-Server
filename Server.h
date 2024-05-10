#ifndef SERVER_H
#define SERVER_H

namespace FrameworkDesign {
	class Server {

	private:
		hreadPool m_threadPool;
		FrameworkDesign::InitController* m_ic;
		MessageController* m_mc;
		PushController* m_pc;
		FriendController* m_fc;

	public:
		void start();

		void processClientRequest(int& fd);

		bool receive();

		void send();
	};
}

#endif
