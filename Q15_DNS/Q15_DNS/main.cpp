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
	
	//		호스트 이름
	cout << "호스트 이름 : " << host->h_name << endl;
	//		별명 검색
	for (int i = 0; host->h_aliases[i]; ++i)
	{
		cout << "별명 검색 : " << host->h_aliases[i] << endl;
	}
	//		주소 타입
	cout << "주소 타입 : " << ((host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6") << endl;

	//		주소 길이
	cout << "주소 길이 : " << host->h_length << endl;
	//		주소 리스트

	for (int i = 0; host->h_addr_list[i]; ++i)
	{
		cout << i << " 번째 주소 : " 
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
	//	//		입력
	//	//	초기화
	//	char Buffer[1024] = { 0, };
	//	//	입력
	//	cout << "메세지 입력 : ";
	//	cin >> Buffer;

	//	//		클라 소켓 주소
	//	SOCKADDR_IN RemoteSockAddr;
	//	memset(&RemoteSockAddr, 0, sizeof(RemoteSockAddr));
	//	int RemoteSockLength = sizeof(RemoteSockAddr);

	//	//		전송, 받기
	//	int SendLength = sendto(ServerSocket, Buffer, strlen(Buffer), 0,
	//		(SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));
	//	int RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0,
	//		(SOCKADDR*)&RemoteSockAddr, &RemoteSockLength);
	//	//	표시
	//	cout << Buffer << endl;
	//}

	//closesocket(ServerSocket);
	WSACleanup();

	return 0;
}