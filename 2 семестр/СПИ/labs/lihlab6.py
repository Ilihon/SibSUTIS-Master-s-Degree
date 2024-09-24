a=10
l=5
fi=0
narr=[10,100,1000,10000,100000,1000000,10000000]

import random as rnd
import math as mt

for n in (narr):
    yes=0
    for i in range (n):
        x=a*rnd.random()
        fi=mt.pi*rnd.random()
        if(x<=l*mt.sin(fi)):
            yes+=1

    Peks=yes/n
    P=(2*l)/(a*mt.pi)
    print("n=",n,"delta", abs(P-Peks)/P, P, Peks)
  