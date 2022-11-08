#include <iostream>
#include <WinSock2.h> // for socket(), connect(), send(), and recv()
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // 라이브러리 시작
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성 
	
	//		메모리 초기화
	SOCKADDR_IN ServerAddr; // 서버 주소
	memset(&ServerAddr, 0, sizeof(SOCKADDR_IN));
	ServerAddr.sin_family = PF_INET; // IPv4
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // host to network, 주소 아무거나 : INADDR_ANY
	ServerAddr.sin_port = htons(1234); // 포트 번호
	
	int Status = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(SOCKADDR_IN)); // 소켓에 주소 할당
	
	Status = listen(ServerSocket, 0); // 연결 대기

	SOCKADDR_IN ClientAddrIn; // 클라이언트 주소
	memset(&ClientAddrIn, 0, sizeof(SOCKADDR_IN));
	int ClientLength = sizeof(ClientAddrIn);
	
	cout << "Server Started" << endl;
	
	//			연결 수락 및 데이터 송수신
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddrIn, &ClientLength);
	cout << "Server Ready to receive" << endl;

	////			메세지 보내기 
	//char Message[] = "hhhhellooo";
	//int SentBytes = send(ClientSocket, Message, strlen(Message), 0);

	//			받은 메세지 
	char Buffer[1024] = {0, }; // 선언 및 초기화 
	int RecvBytes = recv(ClientSocket, Buffer, 1023, 0); // 출력 _ 하나 작은 이유?
	cout << "버퍼 : " << Buffer << ", 받은 양 : " << RecvBytes << endl;
	
	//			보낸 메세지
	cout << "보낼 메세지 : ";
	cin >> Buffer;
	int SentBytes = send(ClientSocket, Buffer, strlen(Buffer), 0);

	
	//			종료
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//끝
	WSACleanup();
	
	
	return 0;
	
}