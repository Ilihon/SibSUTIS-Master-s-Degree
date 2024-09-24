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
#define Q_SIZE 32
using namespace std;
const int ModLen = 400;

int main()
{
    
	char buf[ModLen];
	WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "this is a test";
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    
	memset(buf,0,ModLen);
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
	
    freeaddrinfo(result);
    unsigned char mask[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
    int iSendResult = 0;
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));
	mpz_t p, g, x, y, x1, f, b, A,l,e,d,t1,t2,t3,q,S,ex;
	mpz_init(p);
	mpz_init(g);
	mpz_init(x);
	mpz_init(y);
	mpz_init(x1);
	mpz_init(f);
	mpz_init(b);
	mpz_init(A);
	mpz_init(l);
	mpz_init(e);
	mpz_init(d);
	mpz_init(t1);
	mpz_init(t2);
	mpz_init(t3);
	mpz_init(q);
	mpz_init(S);
	mpz_init(ex);
	FILE *in = fopen("p","r");
	mpz_inp_str (p, in, 16);
	fclose (in);
	in = fopen("g","r");
	mpz_inp_str (g, in, 16);
	fclose (in);
	in = fopen("A","r");
	mpz_inp_str (A, in, 16);
	fclose (in);
	in = fopen("b1","r");
	mpz_inp_str (b, in, 16);
	fclose (in);
	in = fopen("q","r");
	mpz_inp_str (q, in, 16);
	fclose (in);
	gmp_printf("p = %Zx\n", p);
	gmp_printf("g = %Zx\n", g);
	mpz_urandomm(x,state,p);
	gmp_printf("x = %Zx\n", x);
	mpz_powm(y, g, x, p);
	gmp_printf("y = %Zx\n", y);
    iResult = recv(ConnectSocket, buf, ModLen, 0);
	printf("inputkey = %s\n", buf);
	mpz_set_str(x1, buf, 16);
	memset(buf,0,ModLen);
	mpz_get_str (buf, 16, y);
	iSendResult = send(ConnectSocket, buf, ModLen, 0);
  	printf("Bytes sent: %d\n", iSendResult);
  	closesocket(ConnectSocket);
  	WSACleanup();
	mpz_import(ex,32,1,1,0,0,mask);
	mpz_and(d,x1,ex);
	mpz_and(e,y,ex);
	mpz_setbit(d,128);
	mpz_setbit(e,128);
	gmp_printf("d = %Zx\n", d); 
	gmp_printf("e = %Zx\n", e); 
	gmp_printf("x = %Zx\n", y); 
	mpz_mul(t1,e,b);
	mpz_add(t2,x,t1);
	mpz_mod(t1,t2,q);
	mpz_powm(t2, A, d, p);
	mpz_mul(t3,x1,t2);
	mpz_powm(S, t3, t1, p);
  	gmp_printf("S = %Zx\n", S);  
    return 0;
}

