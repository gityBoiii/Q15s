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

	//			�޼��� 
	//		������
	//	�ʱ�ȭ
	char Message[1024] = "";
	cout << "���� �޼��� : ";
	cin >> Message;
	//	������
	char Buffer[1024] = {0, }; // ���� �� �ʱ�ȭ 
	int SentBytes = send(ServerSocket, Message, strlen(Message), 0);
	cout << "���� : " << Message << ", ���� �� : " << SentBytes << endl;

	//		�ޱ�
	int RecvBytes = recv(ServerSocket, Buffer, 1023, 0); // ��� _ �ϳ� ���� ����?
	cout << "���� : " << Buffer << ", ���� �� : " << SentBytes << endl;


	//		����
	closesocket(ServerSocket);
	WSACleanup();
	
	return 0;
}