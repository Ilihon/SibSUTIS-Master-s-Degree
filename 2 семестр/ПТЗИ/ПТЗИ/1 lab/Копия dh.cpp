#include <gmp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <windows.h>
#include <fstream>

using namespace std;
const int ModLen = 128;

int main()
{
 	
    
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
	gmp_randseed_ui(state, 5454646487; 
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
	
	FILE *out = fopen("p","w");
	mpz_out_str (out, 16, p);;
	fclose (out);
	out = NULL;
	out = fopen("g","w");
	mpz_out_str (out, 16, g);
	fclose (out);
	//mpz_get_str (char *str, int base, mpz t op)
//	cout << "Y1 = g^c%p = " <<hex<< g << "^" <<hex<< c << "%" <<hex<< p << " = " <<hex<< y1 << endl << "Y2 = g^d%p = " << hex << g << "^" << hex << d << "%" << hex << p << " = " << hex << y2 << endl;
//	cout << "Z1 = y1^d%p = " <<hex<< y1 << "^" <<hex<< d << "%" <<hex<< p << " = " << z1 << endl << "Z2 = Y2^c%p = " <<hex<< y2 << "^" <<hex<< c << "%" << p << " = " << z2 << endl;
	//cout << "z1 = " << hex << z1 << endl;
	//cout << "z2 = " << hex << z2 << endl;
	
	
	
	system("pause");
    return 0;
}

