#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma  comment(lib,"ws2_32.lib")
int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != S_OK)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket Error Code : " << errCode << endl;
		return 0;
	}

	// 나의 주소
	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "bind Error Code : " << errCode << endl;
		return 0;
	}

	if (::listen(listenSocket, 10) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "listen Error Code : " << errCode << endl;
		return 0;
	}

	// -------------
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);
		
		SOCKET clientSocket = ::accept(listenSocket, reinterpret_cast<SOCKADDR*>(&clientAddr), &addrLen);
		
		if (clientSocket == INVALID_SOCKET)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Accept Error Code : " << errCode << endl;
			return 0;
		}

		// 입장
		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "client connected. IP = " << ipAddress << endl;
	
	}
	// ----------------

	::WSACleanup();
}
