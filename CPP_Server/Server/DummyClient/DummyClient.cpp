
#include "pch.h"
#include <iostream>

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma  comment(lib,"ws2_32.lib")

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != S_OK)
		return 0; 

	// AF : Address family (AF_INET :IPv4, AF_INET6 : IPv6)
	// type : TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
	// protocol : 0
	// return : descriptor

	SOCKET clientSocket =::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode =::WSAGetLastError();
		cout << "Socket Error Code : "<< errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);


	//host to network short
	//Endian issue 떄문에 바로 못넣어줌
	//대부분 cpu ->little endian
	//네트워크 표준 -> big endian

	if (::connect(clientSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Connect Error Code : " << errCode << endl;
		return 0;
	}

	// -------------------
	//연결 성공. 데이터 송수신 가능

	cout << "Connected To Server!" << endl;

	while (true)
	{
		this_thread::sleep_for(1s);
	}

	//--------------------

	// 소켓 리소스 반환
	::closesocket(clientSocket);


	//윈속 종료
	::WSACleanup();
}
