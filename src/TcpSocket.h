#pragma once

#include "include.h"

namespace clservasy
{
	class TcpSocket
	{
	private:
		SOCKET _socket;
		sockaddr_in _address;
		bool _isConnected;

		TcpSocket(SOCKET socket);

		void initWinsock();

	public:
		enum ShutDownType { RECEIVE, SEND, BOTH };

		TcpSocket(int port);
		TcpSocket(std::string address, int port);
		operator SOCKET() const;

		void bind() const;
		void listen() const;
		void send(std::string message) const;
		void connect();
		void shutdown(ShutDownType how);
		void close();

		int receive(std::vector<char>* buffer) const;
		std::string receiveString(size_t bufferSize) const;
		std::string receiveOneLine(size_t bufferSize) const;
		std::string receiveLines(size_t bufferSize) const;
		TcpSocket accept() const;
		bool isConnected() const;

		uint16_t getPort() const;
		std::string getIp() const;
	};
}