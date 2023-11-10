#pragma once
#include "TcpSocket.h"

namespace clservasy
{
	class TcpListenerAsync
	{
	public:

		std::function<void(TcpListenerAsync*, TcpSocket)> clientConnected;
		std::function<void(TcpListenerAsync*, TcpSocket, std::string)> messageReceived;
		std::function<void(TcpListenerAsync*, TcpSocket, std::string)> messageSended;

		TcpListenerAsync(int port, size_t bufferSize = DEFAULT_BUFFER_SIZE);
		TcpListenerAsync(std::string address, int port, size_t bufferSize = DEFAULT_BUFFER_SIZE);

		void start();
		void stop();
		void close();

		bool isListening();

		uint16_t getPort() const;

		void sendTo(TcpSocket socket, std::string message);
		void receiveFrom(TcpSocket socket);
		void receiveOneLineFrom(TcpSocket socket);
		void receiveLinesFrom(TcpSocket socket);

	private:
		TcpSocket _listenSocket;
		bool _isListening;
	};
}