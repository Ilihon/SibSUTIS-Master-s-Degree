#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include <unistd.h>
#include <rdtsc.h>

const int ModLen = 128;

int main()
  {
  char buf [ModLen];
  unsigned int t1, t2, cps;
  mpz_t x, y;
  mpz_init (x);
  mpz_init (y);
  t1 = CC();
  sleep (1);
  t2 = CC();
  cps = t2 - t1;
  srand (time(0));
  for (int i = 0; i < ModLen; i++) buf[i] = rand();
  mpz_import (x, ModLen, 1, 1, 0, 0, buf);
  gmp_printf ("x = %Zx\n", x);
  printf ("\n\n");

  t1 = CC();
  mpz_add (y, x, x);
  t2 = CC();
  printf ("add %d\n", t2 - t1);
  
  t1 = CC();
  mpz_add (y, x, x);
  t2 = CC();
  printf ("add %d\n", t2 - t1);
  

  
  return 0;
}
