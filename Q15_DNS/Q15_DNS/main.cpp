#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	hostent* host = gethostbyname("naver.com");
	
	//		ȣ��Ʈ �̸�
	cout << "ȣ��Ʈ �̸� : " << host->h_name << endl;
	//		���� �˻�
	for (int i = 0; host->h_aliases[i]; ++i)
	{
		cout << "���� �˻� : " << host->h_aliases[i] << endl;
	}
	//		�ּ� Ÿ��
	cout << "�ּ� Ÿ�� : " << ((host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6") << endl;

	//		�ּ� ����
	cout << "�ּ� ���� : " << host->h_length << endl;
	//		�ּ� ����Ʈ

	for (int i = 0; host->h_addr_list[i]; ++i)
	{
		cout << i << " ��° �ּ� : " 
			<< inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]) << endl;
	}



	
	//SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);

	//SOCKADDR_IN ServerSocketAddr;
	//memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
	//ServerSocketAddr.sin_family = PF_INET;
	//ServerSocketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // Union
	//ServerSocketAddr.sin_port = htons(1234);

	//while (true)
	//{
	//	//		�Է�
	//	//	�ʱ�ȭ
	//	char Buffer[1024] = { 0, };
	//	//	�Է�
	//	cout << "�޼��� �Է� : ";
	//	cin >> Buffer;

	//	//		Ŭ�� ���� �ּ�
	//	SOCKADDR_IN RemoteSockAddr;
	//	memset(&RemoteSockAddr, 0, sizeof(RemoteSockAddr));
	//	int RemoteSockLength = sizeof(RemoteSockAddr);

	//	//		����, �ޱ�
	//	int SendLength = sendto(ServerSocket, Buffer, strlen(Buffer), 0,
	//		(SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));
	//	int RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0,
	//		(SOCKADDR*)&RemoteSockAddr, &RemoteSockLength);
	//	//	ǥ��
	//	cout << Buffer << endl;
	//}

	//closesocket(ServerSocket);
	WSACleanup();

	return 0;
}