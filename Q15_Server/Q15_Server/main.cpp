#include <iostream>
#include <WinSock2.h> // for socket(), connect(), send(), and recv()
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // ���̺귯�� ����
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); // ���� ���� 
	
	//		�޸� �ʱ�ȭ
	SOCKADDR_IN ServerAddr; // ���� �ּ�
	memset(&ServerAddr, 0, sizeof(SOCKADDR_IN));
	ServerAddr.sin_family = PF_INET; // IPv4
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // host to network, �ּ� �ƹ��ų� : INADDR_ANY
	ServerAddr.sin_port = htons(1234); // ��Ʈ ��ȣ
	
	int Status = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(SOCKADDR_IN)); // ���Ͽ� �ּ� �Ҵ�
	
	Status = listen(ServerSocket, 0); // ���� ���

	SOCKADDR_IN ClientAddrIn; // Ŭ���̾�Ʈ �ּ�
	memset(&ClientAddrIn, 0, sizeof(SOCKADDR_IN));
	int ClientLength = sizeof(ClientAddrIn);
	
	cout << "Server Started" << endl;
	
	//			���� ���� �� ������ �ۼ���
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddrIn, &ClientLength);
	cout << "Server Ready to receive" << endl;

	////			�޼��� ������ 
	//char Message[] = "hhhhellooo";
	//int SentBytes = send(ClientSocket, Message, strlen(Message), 0);

	//			���� �޼��� 
	char Buffer[1024] = {0, }; // ���� �� �ʱ�ȭ 
	int RecvBytes = recv(ClientSocket, Buffer, 1023, 0); // ��� _ �ϳ� ���� ����?
	cout << "���� : " << Buffer << ", ���� �� : " << RecvBytes << endl;
	
	//			���� �޼���
	cout << "���� �޼��� : ";
	cin >> Buffer;
	int SentBytes = send(ClientSocket, Buffer, strlen(Buffer), 0);

	
	//			����
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//��
	WSACleanup();
	
	
	return 0;
	
}