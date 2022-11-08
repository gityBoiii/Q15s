#include "iostream"
#include <WinSock2.h> // for socket(), connect(), send(), and recv()
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
	
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // ���̺귯�� ����
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); // ���� ���� ����
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0); // Ŭ�� ���� ���� 

	//		�޸� �ʱ�ȭ
	SOCKADDR_IN ServerAddr; // ���� �ּ�
	memset(&ServerAddr, 0, sizeof(SOCKADDR_IN));
	ServerAddr.sin_family = PF_INET; // IPv4
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // host to network, �ּ� �ƹ��ų� : INADDR_ANY
	ServerAddr.sin_port = htons(1234); // ��Ʈ ��ȣ

	int Status = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(SOCKADDR_IN)); // ���Ͽ� �ּ� �Ҵ�
	char Buffer[1024] = { 0, }; // ���� ����. �ʱ�ȭ 
	
	//			Ŭ�� ���� ����
	SOCKADDR_IN ClientAddr; // Ŭ���̾�Ʈ �ּ�
	memset(&ClientAddr, 0, sizeof(SOCKADDR_IN)); // �ּ� �ʱ�ȭ
	int ClientSockLength = sizeof(ClientAddr); // �ּ� ����
	int RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0,
		(SOCKADDR*)&ClientAddr, &ClientSockLength);	// ���� ���
	int SendLength = sendto(ServerSocket, Buffer, RecvLength, 0,
		(SOCKADDR*)&ClientAddr, ClientSockLength);	// �޴� ���
	
	
	
	//			����
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//��
	WSACleanup();

	return 0;
}