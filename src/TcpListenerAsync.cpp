#include "TcpListenerAsync.h"

namespace clservasy
{
	TcpListenerAsync::TcpListenerAsync(int port, size_t bufferSize)
		: _listenSocket(port)
	{
		_listenSocket.bind();
		_isListening = false;
	}

	TcpListenerAsync::TcpListenerAsync(std::string address, int port, size_t bufferSize)
		: TcpListenerAsync(port, bufferSize) {}

	void TcpListenerAsync::start()
	{
		_isListening = true;
		while (_isListening)
		{
			_listenSocket.listen();
			TcpSocket client = _listenSocket.accept();
			std::thread([this, &client]() {
				if (clientConnected)
					clientConnected(this, client);
				}).detach();
		}
	}

	void TcpListenerAsync::stop()
	{
		_isListening = false;
	}

	void TcpListenerAsync::close()
	{
		_listenSocket.close();
	}

	bool TcpListenerAsync::isListening()
	{
		return _isListening;
	}

	uint16_t TcpListenerAsync::getPort() const
	{
		return _listenSocket.getPort();
	}

	void TcpListenerAsync::sendTo(TcpSocket socket, std::string message)
	{
		socket.send(message);
		if (messageSended)
			messageSended(this, socket, message);
	}

	void TcpListenerAsync::receiveFrom(TcpSocket socket)
	{
		std::string message = socket.receiveString(DEFAULT_BUFFER_SIZE);
		if (messageReceived)
			messageReceived(this, socket, message);
	}

	void TcpListenerAsync::receiveOneLineFrom(TcpSocket socket)
	{
		std::string message = socket.receiveOneLine(DEFAULT_BUFFER_SIZE);
		if (messageReceived)
			messageReceived(this, socket, message);

	}

	void TcpListenerAsync::receiveLinesFrom(TcpSocket socket)
	{
		std::string message = socket.receiveLines(DEFAULT_BUFFER_SIZE);
		if (messageReceived)
			messageReceived(this, socket, message);
	}
}
