import random as rnd
import math as mt
import numpy as np
import matplotlib.pyplot as plt
from scipy.special import lambertw

p1treb=1
p1obsl=0.95
n2=3
t1obsl=1/p1obsl
t1treb=1/p1treb
#print(t1obsl,t1treb)




#for i in range (sec):
    #print()
    #print((-mt.log(rnd.random())/t2treb))



narr=[10000]
for sec in narr:
    twarr=[]
    twarr = [0 for i in range(sec+1)]
    twarr[0]=0
    tobslarr=[]
    tobslarr = [0 for i in range(sec+1)]
    tobslarr[0]=tobsl=-mt.log(rnd.random())/p1obsl
    ttrebarr=[]
    ttrebarr = [0 for i in range(sec+1)]
    ttrebarr[0]=rnd.gammavariate(2,p1treb)
    #ttrebarr[0]=abs((-1/p1treb)*lambertw(-rnd.random()/p1treb))
    #rnd.gammavariate(2,p1)
    time=ttrebarr[0]

    for i in range (sec):
        #ochered+=1
        #ttrebarr[i+1]=-mt.log(rnd.random())/p1treb #puasson

        #ttrebarr[i+1]=t1treb #stac

        #ttrebarr[i+1]=abs(-lambertw(-rnd.random()/(p1treb*p1treb))) #erlang 2 por
        ttrebarr[i+1]=rnd.gammavariate(2,p1treb/2)
        #print(ttrebarr[i+1])

        tobslarr[i+1]=-mt.log(rnd.random())/p1obsl
        twarr[i+1]=max(twarr[i]+tobslarr[i]-ttrebarr[i+1],0)
        time+=tobslarr[i+1]
        #print(twarr[i],tobslarr[i],time)
        #print(ttrebarr[i],tobslarr[i],twarr[i])
        #print(tw)
    twarr=np.array(twarr)
    #print(np.average(tobslarr))
    #print(abs(np.average(ttrebarr)))
    #print(np.average(twarr))
    ochered=[]
    ochered = [0 for i in range(sec+1)]
    #print(twarr)
    for i in range(sec):
        tektime=twarr[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr[j-1]
            ochered[i]+=1
            j-=1
        #print(sec,j, len(twarr[ np.where( twarr[0:j] > 0 ) ]))
    np.set_printoptions(precision=3)
    #print(np.array(tobslarr))

    #print(twarr)
    lstx=[]
    lsty=[]
    for i in [10,100,500,1000,5000,9999]:
        x=sum(tobslarr[0:i])
        y=ochered[i]
        print(x,y)
        lstx.append(x)
        lsty.append(y)
        #plt.plot(x, y)
        #plt.xlabel('t - axis')
        # naming the y axis
        #plt.ylabel('ochered - axis')

# corresponding y axis values

  
# plotting the points 
plt.plot(lstx, lsty,label="erlang 2 por")




narr=[10000]
for sec in narr:
    twarr=[]
    twarr = [0 for i in range(sec+1)]
    twarr[0]=0
    tobslarr=[]
    tobslarr = [0 for i in range(sec+1)]
    tobslarr[0]=tobsl=-mt.log(rnd.random())/p1obsl
    ttrebarr=[]
    ttrebarr = [0 for i in range(sec+1)]
    ttrebarr[0]=t1treb
    time=ttrebarr[0]

    for i in range (sec):
        #ochered+=1
        #ttrebarr[i+1]=-mt.log(rnd.random())/p1treb #puasson

        ttrebarr[i+1]=t1treb #stac

        #ttrebarr[i+1]=-lambertw(-rnd.random()/p1treb*p1treb) #erlang 2 por


        tobslarr[i+1]=-mt.log(rnd.random())/p1obsl
        twarr[i+1]=max(twarr[i]+tobslarr[i]-ttrebarr[i+1],0)
        time+=tobslarr[i+1]
        #print(twarr[i],tobslarr[i],time)
        #print(ttrebarr[i],tobslarr[i],twarr[i])
        #print(tw)
    twarr=np.array(twarr)
    #print(np.average(tobslarr))
    #print(np.average(ttrebarr))
    #print(np.average(twarr))
    ochered=[]
    ochered = [0 for i in range(sec+1)]
    #print(twarr)
    for i in range(sec):
        tektime=twarr[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr[j-1]
            ochered[i]+=1
            j-=1
        #print(sec,j, len(twarr[ np.where( twarr[0:j] > 0 ) ]))
    np.set_printoptions(precision=3)
    #print(np.array(tobslarr))

    #print(twarr)
    lstx=[]
    lsty=[]
    for i in [10,100,500,1000,5000,9999]:
        x=sum(tobslarr[0:i])
        y=ochered[i]
        print(x,y)
        lstx.append(x)
        lsty.append(y)
        #plt.plot(x, y)
        #plt.xlabel('t - axis')
        # naming the y axis
        #plt.ylabel('ochered - axis')

# corresponding y axis values
plt.plot(lstx, lsty,label="stac")
  



narr=[10000]
for sec in narr:
    twarr=[]
    twarr = [0 for i in range(sec+1)]
    twarr[0]=0
    tobslarr=[]
    tobslarr = [0 for i in range(sec+1)]
    tobslarr[0]=tobsl=-mt.log(rnd.random())/p1obsl
    ttrebarr=[]
    ttrebarr = [0 for i in range(sec+1)]
    ttrebarr[0]=-mt.log(rnd.random())/p1treb
    time=ttrebarr[0]

    for i in range (sec):
        #ochered+=1
        ttrebarr[i+1]=-mt.log(rnd.random())/p1treb #puasson

        #ttrebarr[i+1]=t1treb #stac

        #ttrebarr[i+1]=-lambertw(-rnd.random()/p1treb*p1treb) #erlang 2 por


        tobslarr[i+1]=-mt.log(rnd.random())/p1obsl
        twarr[i+1]=max(twarr[i]+tobslarr[i]-ttrebarr[i+1],0)
        time+=tobslarr[i+1]
        #print(twarr[i],tobslarr[i],time)
        #print(ttrebarr[i],tobslarr[i],twarr[i])
        #print(tw)
    twarr=np.array(twarr)
    #print(np.average(tobslarr))
    #print(np.average(ttrebarr))
    #print(np.average(twarr))
    ochered=[]
    ochered = [0 for i in range(sec+1)]
    #print(twarr)
    for i in range(sec):
        tektime=twarr[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr[j-1]
            ochered[i]+=1
            j-=1
        #print(sec,j, len(twarr[ np.where( twarr[0:j] > 0 ) ]))
    np.set_printoptions(precision=3)
    #print(np.array(tobslarr))

    #print(twarr)
    lstx=[]
    lsty=[]
    for i in [10,100,500,1000,5000,9999]:
        x=sum(tobslarr[0:i])
        y=ochered[i]
        print(x,y)
        lstx.append(x)
        lsty.append(y)
        #plt.plot(x, y)
        #plt.xlabel('t - axis')
        # naming the y axis
        #plt.ylabel('ochered - axis')

# corresponding y axis values

  
# plotting the points 
plt.plot(lstx, lsty,label="puasson")








# naming the x axis
plt.xlabel('t - axis')
# naming the y axis
plt.ylabel('ochered - axis')
  

plt.legend()
plt.show()