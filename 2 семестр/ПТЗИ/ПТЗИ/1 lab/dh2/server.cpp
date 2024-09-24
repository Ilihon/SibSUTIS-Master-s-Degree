#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501
#include <gmp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;
const int ModLen = 400;

int main()
{
	WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    
	char buf[ModLen];
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));
	mpz_t p, g, x, y, x1, f;
	mpz_init(p);
	mpz_init(g);
	mpz_init(x);
	mpz_init(y);
	mpz_init(x1);
	mpz_init(f);
	FILE *in = fopen("p","r");
	mpz_inp_str (p, in, 16);
	fclose (in);
	in = fopen("g","r");
	mpz_inp_str (g, in, 16);
	fclose (in);
	gmp_printf("p = %Zx\n", p);
	gmp_printf("g = %Zx\n", g);
	mpz_urandomm(x,state,p);
	gmp_printf("x = %Zx\n", x);
	mpz_powm(y, g, x, p);
	gmp_printf("y = %Zx\n", y);
	memset(buf,0,ModLen);
	mpz_get_str (buf, 16, y);
	gmp_printf("buf = %s\n", buf);
	ClientSocket = accept(ListenSocket, NULL, NULL);
    closesocket(ListenSocket);
	iSendResult = send( ClientSocket, buf, ModLen, 0 );
    printf("Bytes sent: %d\n", iSendResult);
    iResult = recv(ClientSocket, buf, ModLen, 0);
	printf("inputkey = %s\n", buf);
	mpz_set_str(x1, buf, 16);
	mpz_powm(f, x1, x, p);
	gmp_printf("result = %Zx\n", f);
	system("pause");
    return 0;
}

