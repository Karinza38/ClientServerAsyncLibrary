#include "TcpClient.h"

using namespace clservasy;

TcpClient::TcpClient(std::string address, int port, ProtocolType type, size_t bufferSize) : _connectSocket(address, port)
{
	_bufferSize = bufferSize;
}

TcpClient::~TcpClient()
{
	stop();
	_connectSocket.close();
}

void TcpClient::connect()
{
	try
	{
		_connectSocket.connect();
	}
	catch (const std::exception&)
	{
		std::cout << "Failed to connect\n";
	}
	connected(this, _connectSocket);
}

void TcpClient::start()
{
	if (!_connectSocket.isConnected())
	{
#ifdef _WIN32
		throw std::exception("You wasn't connected\n");
#else
		throw std::exception();
#endif
	}

	std::thread([&] {receiveMessagesFromServer(); }).detach();

	while (true)
	{
		std::string message;
		std::string line;
		std::getline(std::cin, message);

		try {
			_connectSocket.send(message);
			_connectSocket.send("\r\n");
			}
		catch (const std::exception&) { return; }
	}
}
void TcpClient::stop()
{
	_connectSocket.shutdown(TcpSocket::ShutDownType::BOTH);
}
void TcpClient::receiveMessagesFromServer()
{
	while (true)
	{
		if (messageReceived) {
			try { messageReceived(this, _connectSocket.receiveString(_bufferSize)); }
			catch (const std::exception&) { std::cout << ""; return; }
		}
	}
}