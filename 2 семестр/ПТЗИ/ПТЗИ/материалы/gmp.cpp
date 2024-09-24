#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include <unistd.h>
#include <rdtsc.h>

const int ModLen = 127;

int main()
  {
  char buf [ModLen];
  unsigned int t1, t2, cps;
  mpz_t q, p;
  mpz_init (q);
  mpz_init (p);
  srand (time(0));
  for (int i = 0; i < ModLen; i++) 
  	  buf[i] = rand();
  mpz_import (q, ModLen, 1, 1, 0, 0, buf);
  mpz_mul_ui (p, q, 2);
  mpz_add_ui (p, p, 1);
  gmp_printf ("1 q = %Zx\n", q);
  gmp_printf ("1 p = %Zx\n", p);
  for(;(mpz_probab_prime_p (p, 50) == 0) || (mpz_probab_prime_p (q, 50) == 0);){
  	mpz_clear (p);
  	//mpz_realloc2(p, 128);
  	for(;mpz_probab_prime_p (q, 50) == 0;){
  		mpz_clear (q);
  		//mpz_realloc2(q,127);
		for (int i = 0; i < ModLen; i++) 
	  		buf[i] = rand();
   		mpz_import (q, ModLen, 1, 1, 0, 0, buf);
    }
  	gmp_printf ("prime q = %Zx\n", q);
  	mpz_mul_ui (p, q, 2);
  	mpz_add_ui (p, p, 1);
  }
  gmp_printf ("prime p = %Zx\n", p);
  printf ("");
  printf ("\n\n");
  return 0;
}
