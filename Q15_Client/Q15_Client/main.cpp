#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <string.h>

#pragma comment(lib, "WS2_32.lib")
using namespace std;

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSocketAddr;
	memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
	ServerSocketAddr.sin_family = PF_INET;
	ServerSocketAddr.sin_addr.s_addr = inet_addr("172.16.2.104");
	ServerSocketAddr.sin_port = htons(4949);

	connect(ServerSocket, (sockaddr*)&ServerSocketAddr, sizeof(ServerSocketAddr));

	//			메세지 
	//		보내기
	//	초기화
	char Message[1024] = "";
	cout << "보낼 메세지 : ";
	cin >> Message;
	//	보내기
	char Buffer[1024] = {0, }; // 선언 및 초기화 
	int SentBytes = send(ServerSocket, Message, strlen(Message), 0);
	cout << "버퍼 : " << Message << ", 보낸 양 : " << SentBytes << endl;

	//		받기
	int RecvBytes = recv(ServerSocket, Buffer, 1023, 0); // 출력 _ 하나 작은 이유?
	cout << "버퍼 : " << Buffer << ", 받은 양 : " << SentBytes << endl;


	//		종료
	closesocket(ServerSocket);
	WSACleanup();
	
	return 0;
}