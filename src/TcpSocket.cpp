#include "TcpSocket.h"

namespace clservasy
{
	TcpSocket::TcpSocket(std::string address, int port) : TcpSocket(port)
	{
		inet_pton(AF_INET, address.c_str(), &_address.sin_addr.s_addr) < 0;
	}

	TcpSocket::operator SOCKET() const
	{
		return _socket;
	}
	TcpSocket::TcpSocket(int port)
	{
		initWinsock();
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = htonl(INADDR_ANY);
		_address.sin_port = htons(port);
	}
#pragma warning(disable : 26495)
	TcpSocket::TcpSocket(SOCKET socket)
	{
		_socket = socket;
	}
#pragma warning(default : 26495)

	void TcpSocket::initWinsock()
	{
#ifdef _WIN32
		WSADATA wsaData;
		int initError = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (initError != 0)
			throw std::exception("WSAStartup() failed\n");
#endif
	}

	void TcpSocket::bind() const
	{
		int bytesCount = ::bind(_socket, (sockaddr*)&_address, sizeof(_address));
		if (bytesCount == SOCKET_ERROR)
#ifdef _WIN32
			throw std::exception("Binding failed\n");
#else
			throw std::exception();
#endif
	}

	void TcpSocket::listen() const
	{
		int error = ::listen(_socket, 50);
		if (error == SOCKET_ERROR)
#ifdef _WIN32
			throw std::exception("Listening failed\n");
#else
			throw std::exception();
#endif
	}

	void TcpSocket::connect()
	{
		int error = ::connect(_socket, (sockaddr*)&_address, sizeof(_address));
		if (error == SOCKET_ERROR)
#ifdef _WIN32
			throw std::exception("Connection failed\n");
#else
			throw std::exception();
#endif

		_isConnected = true;
	}

	void TcpSocket::send(std::string message) const
	{
		std::vector<char> buffer(message.begin(), message.end());
		if (buffer.empty()) return;
		int bytesCount = ::send(_socket, &buffer[0], buffer.size(), 0);
		if (bytesCount == SOCKET_ERROR)
#ifdef _WIN32
			throw std::exception("Sending failed\n");
#else
			throw std::exception();
#endif
	}

	void TcpSocket::close()
	{
#ifdef _WIN32
		_socket = closesocket(_socket);
#else
		_socket = ::close(_socket);
#endif
		_isConnected = false;
	}

	void TcpSocket::shutdown(ShutDownType how)
	{
		_socket = ::shutdown(_socket, how);
	}

	int TcpSocket::receive(std::vector<char>* buffer) const
	{
		int bytesCount = recv(_socket, &(*buffer)[0], (*buffer).size(), 0);
		if (bytesCount == SOCKET_ERROR)
#ifdef _WIN32
			throw std::exception("Receiving failed\n");
#else
			throw std::exception();
#endif
		return bytesCount;
	}

	std::string TcpSocket::receiveString(size_t bufferSize) const
	{
		std::vector<char> buffer(bufferSize);
		int bytesCount = receive(&buffer);
		if (bytesCount <= bufferSize) {
			buffer.resize(bytesCount);
		}
		return std::string(buffer.begin(), buffer.end());
	}

	std::string TcpSocket::receiveOneLine(size_t bufferSize) const
	{
		auto msg = receiveString(bufferSize);
		return std::string(msg.begin(), msg.begin() + msg.find("\r\n"));
	}

	std::string TcpSocket::receiveLines(size_t bufferSize) const
	{
		std::string message = receiveString(bufferSize);
		while (message.empty() || message[message.size() - 1] != '\n')
			message += receiveString(bufferSize);
		return message;
	}

	TcpSocket TcpSocket::accept() const
	{
		SOCKET newSocket = ::accept(_socket, nullptr, nullptr);
		return newSocket;
	}
	bool TcpSocket::isConnected() const
	{
		return _isConnected;
	}
	uint16_t TcpSocket::getPort() const
	{
		return htons(_address.sin_port);
	}
	std::string TcpSocket::getIp() const
	{
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(_address.sin_addr), str, INET_ADDRSTRLEN);
		return str;
	}
}