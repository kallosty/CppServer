#include "pch.h"
#include "ThreadManager.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

/*---------------------------
	Server
----------------------------*/

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << "Send ErrorCode : " << errCode << endl;
}

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData))
		return 0;

	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = htons(7777);

	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		HandleError("Bind");
		return 0;
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		char recvBuffer[1000];

		int32 recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0, 
			(SOCKADDR*)&clientAddr,&addrLen);

		if (recvLen <= 0)
		{
			HandleError("RecvFrom");
			return 0;
		}

		cout << "Recv Data! Len = " << recvBuffer << endl;
		cout << "Recv Data! Len = " << recvLen << endl;

		int32 errCode = ::sendto(serverSocket, recvBuffer, recvLen,0 , (SOCKADDR*)&clientAddr, addrLen);
		if (errCode == SOCKET_ERROR)
		{
			HandleError("SendTo");
			return 0;
		}

		cout << "Send Data! Len = " << sizeof(recvBuffer) << endl;
	}

	::WSACleanup();
}