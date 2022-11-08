#include "iostream"
#include <WinSock2.h> // for socket(), connect(), send(), and recv()
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
	
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // 라이브러리 시작
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0); // 클라 소켓 생성 

	//		메모리 초기화
	SOCKADDR_IN ServerAddr; // 서버 주소
	memset(&ServerAddr, 0, sizeof(SOCKADDR_IN));
	ServerAddr.sin_family = PF_INET; // IPv4
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // host to network, 주소 아무거나 : INADDR_ANY
	ServerAddr.sin_port = htons(1234); // 포트 번호

	int Status = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(SOCKADDR_IN)); // 소켓에 주소 할당
	char Buffer[1024] = { 0, }; // 받을 정보. 초기화 
	
	//			클라 버퍼 정보
	SOCKADDR_IN ClientAddr; // 클라이언트 주소
	memset(&ClientAddr, 0, sizeof(SOCKADDR_IN)); // 주소 초기화
	int ClientSockLength = sizeof(ClientAddr); // 주소 길이
	int RecvLength = recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0,
		(SOCKADDR*)&ClientAddr, &ClientSockLength);	// 보낸 사람
	int SendLength = sendto(ServerSocket, Buffer, RecvLength, 0,
		(SOCKADDR*)&ClientAddr, ClientSockLength);	// 받는 사람
	
	
	
	//			종료
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//끝
	WSACleanup();

	return 0;
}