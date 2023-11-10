#pragma once
#pragma comment(lib, "ws2_32.lib")

#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#define SOCKET_ERROR -1
typedef int SOCKET;
#endif


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <functional>

//#include "Delegate.h"
#include "GeneralPurpose.h"

namespace clservasy
{
	enum ProtocolType { TCP = IPPROTO_TCP, HOP_BY_HOP = IPPROTO_HOPOPTS };

	constexpr char THIS_ADDRESS[10] = "127.0.0.1";
	constexpr uint16_t DEFAULT_PORT = 2023;
	constexpr short DEFAULT_BUFFER_SIZE = 512;
}