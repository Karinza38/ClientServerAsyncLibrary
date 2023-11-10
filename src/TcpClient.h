#pragma once
#include "TcpSocket.h"

class TcpClient
{
private:
	
	size_t _bufferSize;
	clservasy::TcpSocket _connectSocket;

	void receiveMessagesFromServer();

public:

	std::function<void(void*, clservasy::TcpSocket)> connected;
	std::function<void(void*, std::string)> messageReceived;

	TcpClient(
		std::string address,
		int port,
		clservasy::ProtocolType type = clservasy::ProtocolType::TCP,
		size_t bufferSize = 512);
	~TcpClient();

	void connect();
	void start();
	void stop();

};