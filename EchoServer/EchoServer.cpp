#define WIN32_LEAN_AND_MEAN  //exclued unneeded header files

#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<Windows.h>
#include<ws2tcpip.h>
//#include<pthread.h>
#include<string.h>
//#include<strsafe.h>
#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 512
#define PORT "9999"
//DWORD WINAPI InstanceThread(LPVOID);
//VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);
//int has_connected = 0; DWORD ID = 0;
//HANDLE hp = INVALID_HANDLE_VALUE; HANDLE ht = NULL;


int main() {
	//initiate use of WinSock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);  //0000001000000010 = 2^9+2 = 514
	if (iResult != 0) {
		printf("WSAStartup failed with error %d\n", iResult);
		return 1;
	}
	// Create listening socket
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	iResult = getaddrinfo(NULL, PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error %d\n", iResult);
		WSACleanup();
		return 1;
	}
	SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	// bind
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	// listen
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Server is listening\n");

	// accept
	SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ListenSocket);

	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	// recv and send
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);
	iResult = recv(ClientSocket, buf, BUF_SIZE, 0);
	if (iResult > 0) {
		printf("Received %s\n", buf);
		// send position has been moved here. Echo server echo backs only if it received msg
		int iResultSend = send(ClientSocket, buf, BUF_SIZE, 0);
		if (iResultSend == SOCKET_ERROR) {
			printf("Send failed %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
		printf("Sent %s\n", buf);
	}
	else if (iResult == 0) {
		printf("Closing connection");
	}
	else if (iResult == SOCKET_ERROR) {
		//previously, it printed a wrong msg "bind failed ..."
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
	return 0;	
}

