#include "netWork.h"

int Network::createSocket() {}

int Network::bindSocket() {}

int Network::listenSocket() {}

int Network::acceptSocket() {}

void Network::closeSocket() {}

int Network::pollSocket() {}

void Network::sendMessage(int conn, char *buf) {}

void Network::receiveMessage(char *buffer) {}

int Network::sendFile(std::string path) {}
