#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
	WSAData  WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = PF_INET;
	ListenSockAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(4949);

	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, 5);

	fd_set Reads;
	fd_set Copys;
	FD_ZERO(&Reads);

	FD_SET(ListenSocket, &Reads);

	TIMEVAL TimeOut;
	TimeOut.tv_sec = 1;
	TimeOut.tv_usec = 10;

	while (true)
	{
		Copys = Reads;
		int fd_num = select(0, &Copys, 0, 0, &TimeOut);
		if (fd_num == SOCKET_ERROR)
		{
			cout << "error" << endl;
			exit(-1);
		}
		else if (fd_num == 0)
		{
			//cout << "Timeout" << endl;
			//니 서버일 그냥해.
		}
		else
		{
			//니 소켓 변화가 있다. 니 할일 해라.
			//OS가 감시 소켓 바뀌었다는데 너 바뀠었냐?
			for (int i = 0; i < (int)Reads.fd_count; ++i)
			{
				if (FD_ISSET(Reads.fd_array[i], &Copys))
				{
					if (Reads.fd_array[i] == ListenSocket)
					{
						//연결 요청 처리
						SOCKADDR_IN ClientSockAddr;
						memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
						int ClientSockAddrLength = sizeof(ClientSockAddr);
						SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
						FD_SET(ClientSocket, &Reads);
						cout << "Connect : " << ClientSocket << endl;
					}
					else
					{
						char Buffer[1024] = { 0 , };
						int RecvLength = recv(Reads.fd_array[i], Buffer, sizeof(Buffer) - 1, 0);

						//연결 끊김 처리
						if (RecvLength <= 0)
						{
							cout << "Disconnect : " << Reads.fd_array[i] << endl;
							SOCKET DisconnectSocket = Reads.fd_array[i];
							FD_CLR(DisconnectSocket, &Reads);
							closesocket(DisconnectSocket);
						}
						else
						{
							//메세지 받음 처리
							cout << "Client Send : " << Buffer << endl;
							for (int j = 0; j < (int)Reads.fd_count; ++j)
							{
								//Listen Socket 이외의 연결에 메세지 다보내기
								if (Reads.fd_array[j] != ListenSocket)
								{
									int SendLength = send(Reads.fd_array[j], Buffer, RecvLength, 0);
								}

							}
						}
					}
				}
			}
		}
	}



	WSACleanup();
	return 0;
}