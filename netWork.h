#ifndef NETWORK_H
#define NETWORK_H

namespace FrameworkDesign {
	class netWork {

	private:
		int m_listenFd;

	public:
		int createSocket();

		int bindSocket();

		int listenSocket();

		int acceptSocket();

		void closeSocket();

		int pollSocket();

		void sendMessage(char* buf, size_t size);

		void receiveMessage(char* buffer);

		int sendFile(string path);
	};
}

#endif
