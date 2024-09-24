import random as rnd
import scipy.stats as ss
import numpy as np
import matplotlib.pyplot as plt
import time
convlength=50
left=-10
right=11
x = np.arange(left, right)
xU, xL = x +0.5, x - 0.5
prob = ss.norm.cdf(xU, scale = 3) - ss.norm.cdf(xL, scale = 3)
prob = prob / prob.sum() # normalize the probabilities so their sum is 1


asyn=[]
syn=[]
otn=[]
elementslist = [1000,2000,3000,4000,5000,6000,7000,8000,9000,10000]

for elem in elementslist:
    elements=elem
    tacts=np.zeros(convlength)
    boolconv=np.zeros(convlength+1)
    tacts[0] = np.random.choice(x+right, size = 1, p = prob)
    boolconv[0]=1
    timebeginas=time.perf_counter()
    while(1):
        for i in range(convlength):
            if (tacts[i]>0):
                tacts[i]-=1
            if tacts[i]==0:
                if i!=convlength-1 and i!=0 and boolconv[i+1]==0:
                    boolconv[i+1]=1
                    boolconv[i]=0
                    tacts[i+1] = np.random.choice(x+right, size = 1, p = prob)
                if i==convlength-1:
                    boolconv[i]=0
                    elements-=1
                if i==0:
                    boolconv[i]=1
                    tacts[i] = np.random.choice(x+right, size = 1, p = prob)         
        if(elements==0):
            break
    timendas=time.perf_counter()
    asyn.append(timendas-timebeginas)
    print(timendas-timebeginas)
    elements=elem
    tacts=np.zeros(convlength)
    boolconv=np.zeros(convlength+1)
    tacts[0] = np.random.choice(x+right, size = 1, p = prob)
    boolconv[0]=1
    timebegin=time.perf_counter() 
    while(1):
        #gltacts+=1
        for i in range(convlength):
            
            if (tacts[i]>0):
                tacts[i]-=1
            if np.all(tacts==0):
                for j in range(convlength):
                    tacts=np.random.choice(x+right, size = convlength, p = prob)   
                elements-=1  
        if(elements==0):
            break
    timend=time.perf_counter()
    print(timend-timebegin)
    syn.append(timend-timebegin)
    otn.append((timendas-timebeginas)/(timend-timebegin))
        
plt.plot(elementslist, asyn,label="async")
plt.plot(elementslist, syn,label="sync")
plt.legend()
plt.show()
plt.plot(elementslist, otn,label="otn")
plt.legend()
plt.show()