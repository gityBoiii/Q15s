#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);
	
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
		
	SOCKADDR_IN ServerSocketAddr;
	memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
	ServerSocketAddr.sin_family = PF_INET;
	ServerSocketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // Union
	ServerSocketAddr.sin_port = htons(1234);

	while (true)
	{
		//		입력
		//	초기화
		char Buffer[1024] = { 0, };
		//	입력
		cout << "메세지 입력 : ";
		cin >> Buffer;

		//		클라 소켓 주소
		SOCKADDR_IN RemoteSockAddr;
		memset(&RemoteSockAddr, 0, sizeof(RemoteSockAddr));
		int RemoteSockLength = sizeof(RemoteSockAddr);

		//		전송, 받기
		int SendLength = sendto(ServerSocket, Buffer, strlen(Buffer), 0, 
			(SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));
		int RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0,
			(SOCKADDR*)&RemoteSockAddr, &RemoteSockLength);
		//	표시
		cout << Buffer << endl;
	}

	closesocket(ServerSocket);
	WSACleanup();
	
	return 0;
}