#include <gmp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <windows.h>
#include <fstream>
#define Q_SIZE 32
#define B_SIZE 96
using namespace std;
const int ModLen = 128;

int main()
{
	srand(time(0));
	unsigned char buf[ModLen];
	mpz_t q, p, g, res, y1, y2, z1, z2,x1,x2,b,t,r;
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
	mpz_init(b);
	mpz_init(t);
	mpz_init(r);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0)); 
	mpz_urandomb(q, state, Q_SIZE*8);
	if (mpz_probab_prime_p(q, 15) == 0)
		mpz_nextprime(q, q);
	mpz_urandomb(b, state, B_SIZE*8);
	mpz_mul(p, q, b); 
	mpz_add_ui(p, p, 1);
	for (; mpz_probab_prime_p(p, 15) == 0;){
	  mpz_nextprime(q, q);
		mpz_urandomb(b, state, B_SIZE*8);
		mpz_mul(p, q, b);
		mpz_add_ui(p, p, 1);
	}
	mpz_set_ui(t, 2);
	mpz_powm(g, t, b, p);
	mpz_powm(r, g, q, p);
	for (;mpz_cmp_ui(r, 1) != 0 && mpz_cmp_ui(g, 1) == 0;){
		mpz_add_ui(t, t, 1);
		mpz_powm(g, t, b, p);
		mpz_powm(r, g, q, p);
	}
	
	gmp_printf("final g = %Zx\n", g);
  gmp_printf("final p = %Zx\n", p);
	FILE *out = fopen("p","w");
	mpz_out_str (out, 16, p);;
	fclose (out);
	out = NULL;
	out = fopen("g","w");
	mpz_out_str (out, 16, g);
	fclose (out);
	
	system("pause");
    return 0;
}

