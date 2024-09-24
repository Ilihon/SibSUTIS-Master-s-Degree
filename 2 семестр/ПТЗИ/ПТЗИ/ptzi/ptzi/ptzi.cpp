// ptzi.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "..\cryptopp565\cryptlib.h"
#include "..\cryptopp565\hex.h"
#include "..\cryptopp565\osrng.h"
using namespace std;
using namespace CryptoPP;
using CryptoPP::AutoSeededRandomPool;

#include "..\cryptopp565\integer.h"
using CryptoPP::Integer;

#include "..\cryptopp565\nbtheory.h"
using CryptoPP::ModularExponentiation;

#include "..\cryptopp565\dh.h"
using CryptoPP::DH;

#include "..\cryptopp565\secblock.h"
using CryptoPP::SecByteBlock;


int main()
{
	AutoSeededRandomPool prng;
	Integer p, q, g;
	PrimeAndGenerator pg;

	pg.Generate(1, prng, 512, 511);
	p = pg.Prime();
	q = pg.SubPrime();
	g = pg.Generator();

	DH dh(p, q, g);
	SecByteBlock t1(dh.PrivateKeyLength()), t2(dh.PublicKeyLength());
	dh.GenerateKeyPair(prng, t1, t2);
	Integer k1(t1, t1.size()), k2(t2, t2.size());

	cout << "Private key:\n";
	cout << hex << k1 << endl;
	cout << "Public key:\n";
	cout << hex << k2 << endl;
    return 0;
}

