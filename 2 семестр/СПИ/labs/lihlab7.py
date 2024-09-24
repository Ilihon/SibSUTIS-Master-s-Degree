import math as mt
import random as rnd
Npas=0
Npogl=0
Nreflect=0
def xkmodify(xk,SIGMA,cosfi):
    global N0
    
    psi=rnd.random()
    if(psi<=SIGMAa/SIGMA): 
        raise Exception
        
    lambd=(-1/SIGMA)*mt.log(1-psi)
    ans=xk+lambd*cosfi
    cosfi=2*rnd.random()-1  
    return xk+lambd*cosfi,cosfi


h=20
SIGMAa=0.0199
SIGMAs=0.1
SIGMA=SIGMAa+SIGMAs

n=100000
for i in range(n):
    x=0
    cosfi=1
    while(1):
        try:
            x,cosfi=xkmodify(x,SIGMA,cosfi)
        except:
            Npogl+=1
            break
        if x>h:
            Npas+=1
            break
        else:
            if x<0:
                Nreflect+=1
                break
print(Npogl/n+Nreflect/n+Npas/n)
