

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib") //indicates linketer to link .lib file
#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "9999"

int main() {

	//Initiate Winsock - WSAStartup
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //00000010 000000010 = 2^9+2 = 514
	if (iResult != 0) {
		printf("WSAStartup failed with %d\n", iResult);
		return 1;
	}
	
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with %d\n", iResult);
		WSACleanup();
		return 1;
	}

	SOCKET ClientSocket = INVALID_SOCKET;
	// Create a socket and try to connect. Repeat it until it works.
	for (struct addrinfo* curr = result; curr != NULL; curr = curr->ai_next) {
		ClientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ClientSocket == INVALID_SOCKET) {
			printf("socket failed\n");
			WSACleanup();
			return 1;
		}
		iResult = connect(ClientSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("connect failed\n");
			ClientSocket = INVALID_SOCKET;
		}
		else { break; }
	}
	// Recv send 
	char sendData[20] = "This is a test";
	send(ClientSocket, sendData, 20, 0);
	printf("sent %s\n", sendData);
	char receivedData[DEFAULT_BUFLEN];
	ZeroMemory(receivedData, DEFAULT_BUFLEN);
	recv(ClientSocket, receivedData, DEFAULT_BUFLEN, 0);
	printf("Received %s\n", receivedData);


	// Cleanup
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}