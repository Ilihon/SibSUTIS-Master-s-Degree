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
const int ModLen = 128;

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

    // Accept a client socket
    
    
	srand(time(0));
	unsigned char buf[ModLen];
	mpz_t q, p, g, res, y1, y2, z1, z2,x1,x2;
	mpz_init(q);
	mpz_init(p);
	mpz_init(g);
	mpz_init(res);
	mpz_init(x1);
	mpz_init(x2);
	mpz_init(y1);
	mpz_init(y2);
	mpz_init(z1);
	mpz_init(z2);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, 5454646487);
	//gmp_randinit_lc_2exp_size(state, 127);
	//cout <<" q prime? " <<mpz_probab_prime_p(q,50)<<endl;
	//mpz_set_ux(q, 21);
	//mpz_urandomb(q, state, 1023);
	for (int i = 0; i < ModLen; i++)
		buf[i] = rand();
	mpz_import(q, ModLen, 1, 1, 0, 0, buf);
	if (mpz_probab_prime_p(q, 15) == 0)
		mpz_nextprime(q, q);
	mpz_mul_ui(p, q, 2);
	mpz_add_ui(p, p, 1);
	for (; mpz_probab_prime_p(p, 15) == 0;)
	{
	
//		cout << "q = " << hex << q << endl;
//		cout << "bits: " << dec << mpz_popcount(q) << endl;
//		cout << "p = " << hex << p << endl;
//		cout << "bits: " << dec << mpz_popcount(p) << endl;
//		gmp_printf("q = %Zx\n", q);
//		printf("bits: %d\n", mpz_popcount(q));
//		gmp_printf("p = %Zx\n", p);
//		printf("bits: %d\n", mpz_popcount(p));
		mpz_nextprime(q, q);
		mpz_mul_ui(p, q, 2);
		mpz_add_ui(p, p, 1);
	}
	//cout <<"final q = "<< hex << q << endl;
	//cout << "bits: " << dec << mpz_popcount(q) << endl;
	//cout <<"final p = "<< hex << p << endl;
	//cout << "bits: " << dec << mpz_popcount(p) << endl;
	gmp_printf("final q = %Zx\n", q);
	printf("bits: %d\n", mpz_popcount(q));
	gmp_printf("final p = %Zx\n", p);
	printf("bits: %d\n", mpz_popcount(p));
	//cout << endl;
	mpz_set_ui(g, 2);
	mpz_powm(res,g,q,p);
	for (; mpz_cmp_ui(res,1) != 0;)
	{
		mpz_add_ui(g, g, 1);
		mpz_powm(res, g, q, p);
	}
	gmp_printf("final g = %Zx\n", g);
	printf("bits: %d\n", mpz_popcount(g));
	//cout << "res = " << dec << res << endl;
	//cout << "g = " << hex << g << endl;
	//cout << "bits: " << dec << mpz_popcount(g) << endl;
	mpz_urandomm(x1, state, p);
	mpz_urandomm(x2, state, p);
	gmp_printf("x1 = %Zx\n", x1);
	gmp_printf("x2 = %Zx\n", x2);
//	cout << "c = " << hex << c << endl;
//	cout << "d = " << hex << d << endl;
	mpz_powm(y1, g, x1, p);
	mpz_powm(y2, g, x2, p);
	mpz_powm(z1, y1, x2, p);
	mpz_powm(z2, y2, x1, p);
	gmp_printf("z1 = %Zx\n", z1);
	gmp_printf("z2 = %Zx\n", z2);
	ofstream out("params", ios::binary | ios::out);
	if (!out) cout << "error2";
	out.write((char *)&p, sizeof(p));
	out.close();
	//mpz_get_str (char *str, int base, mpz t op)
//	cout << "Y1 = g^c%p = " <<hex<< g << "^" <<hex<< c << "%" <<hex<< p << " = " <<hex<< y1 << endl << "Y2 = g^d%p = " << hex << g << "^" << hex << d << "%" << hex << p << " = " << hex << y2 << endl;
//	cout << "Z1 = y1^d%p = " <<hex<< y1 << "^" <<hex<< d << "%" <<hex<< p << " = " << z1 << endl << "Z2 = Y2^c%p = " <<hex<< y2 << "^" <<hex<< c << "%" << p << " = " << z2 << endl;
	//cout << "z1 = " << hex << z1 << endl;
	//cout << "z2 = " << hex << z2 << endl;
	ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    // No longer need server socket
    closesocket(ListenSocket);
    
	iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
	
	
	
	system("pause");
    return 0;
}

