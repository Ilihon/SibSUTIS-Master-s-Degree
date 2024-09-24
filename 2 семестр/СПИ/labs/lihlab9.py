import random as rnd
import math as mt
import numpy as np
import matplotlib.pyplot as plt

p1treb=1
p2treb=1
p1obsl=0.9
p2obsl=0.3
n2=3
t1obsl=1/p1obsl
t2obsl=1/p2obsl
t1treb=1/p1treb
t2treb=1/p2treb
#print(t1obsl,t1treb)




#for i in range (sec):
    #print()
    #print((-mt.log(rnd.random())/t2treb))



narr=[100000]
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
        ttrebarr[i+1]=-mt.log(rnd.random())/p1treb
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
    for i in [10,100,500,1000,5000,10000,50000,99999]:
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
plt.plot(lstx, lsty,label="odin pribor")
  
# naming the x axis
plt.xlabel('t - axis')
# naming the y axis
plt.ylabel('ochered - axis')
  

  
# function to show the plot
#plt.show()
   
    #twarr[twarr<0] = 0
    #print("\n\n")

import random as rnd
import math as mt
import numpy as np
import matplotlib.pyplot as plt
p1treb=1
p2treb=1
p1obsl=0.9
p2obsl=0.3
n2=3
t1obsl=1/p1obsl
t2obsl=1/p2obsl
t1treb=1/p1treb
t2treb=1/p2treb
#print(t1obsl,t1treb)




#for i in range (sec):
    #print()
    #print((-mt.log(rnd.random())/t2treb))

sec=100000


for sec in [sec]:
    size=int(sec/3)+2
    #print(size)
    twarr=[]
    twarr = [0 for i in range(size)]
    twarr[0]=0
    twarr2=[]
    twarr2 = [0 for i in range(size)]
    twarr2[0]=0
    twarr3=[]
    twarr3 = [0 for i in range(size)]
    twarr3[0]=0
    tobslarr=[]
    tobslarr = [0 for i in range(sec+1)]
    tobslarr[0]=-mt.log(rnd.random())/p2obsl
    
    tobslarr2=[]
    tobslarr2 = [0 for i in range(sec+1)]
    tobslarr2[0]=-mt.log(rnd.random())/p2obsl

    tobslarr3=[]
    tobslarr3 = [0 for i in range(sec+1)]
    tobslarr3[0]=-mt.log(rnd.random())/p2obsl

    ttrebarr=[]
    ttrebarr = [0 for i in range(sec+1)]
    ttrebarr[0]=-mt.log(rnd.random())/p2treb
    ttrebarr2=[]
    ttrebarr2 = [0 for i in range(sec+1)]
    ttrebarr2[0]=-mt.log(rnd.random())/p2treb
    ttrebarr3=[]
    ttrebarr3 = [0 for i in range(sec+1)]
    ttrebarr3[0]=-mt.log(rnd.random())/p2treb  
    a=0
    b=0
    c=0
    for i in range (sec):
        ttrebarr[i+1]=-mt.log(rnd.random())/p2treb

        #print(i)
        if(i%3==0):
            
            tobslarr[i+1]=-mt.log(rnd.random())/p2obsl
            twarr[a+1]=max(twarr[a]+tobslarr[a]-ttrebarr[a+1]-ttrebarr2[b]-ttrebarr3[c],0)
            a+=1
        if(i%3==1):  
            tobslarr2[i+1]=-mt.log(rnd.random())/p2obsl
            twarr2[b+1]=max(twarr2[b]+tobslarr2[b]-ttrebarr2[b+1]-ttrebarr[a]-ttrebarr3[c],0)
            b+=1
        if(i%3==2):
            tobslarr3[i+1]=-mt.log(rnd.random())/p2obsl
            twarr3[c+1]=max(twarr3[c]+tobslarr3[c]-ttrebarr3[c+1]-ttrebarr[a]-ttrebarr2[b],0)
            c+=1

        

    twarr=np.array(twarr)
    twarr2=np.array(twarr2)
    twarr3=np.array(twarr3)

    #print(twarr)
    #print(twarr2)
    #print(twarr3)

    ochered=[]
    ochered = [0 for i in range(sec+1)]
    ochered2=[]
    ochered2 = [0 for i in range(sec+1)]
    ochered3=[]
    ochered3 = [0 for i in range(sec+1)]
    
    for i in range(len(twarr)):
        tektime=twarr[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr[j-1]
            ochered[i]+=1
            j-=1
    
    for i in range(len(twarr2)):
        tektime=twarr2[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr2[j-1]
            ochered2[i]+=1
            j-=1

    for i in range(len(twarr3)):
        tektime=twarr3[i]
        j=i
        while(tektime>0):
            tektime-=tobslarr3[j-1]
            ochered3[i]+=1
            j-=1    
    
    np.set_printoptions(precision=3)


    lstx=[]
    lsty=[]
    for i in [int(10/3),int(100/3),int(500/3),int(1000/3),int(5000/3),int(10000/3),int(50000/3),int(99999/3)]:
        x=sum(tobslarr[0:i])+sum(tobslarr2[0:i])+sum(tobslarr3[0:i])
        y=ochered[i]+ochered2[i]+ochered3[i]
        lstx.append(x)
        lsty.append(y)
        print(x,y)


plt.plot(lstx, lsty,label="tri pribora")
  
# naming the x axis
plt.xlabel('t - axis')
# naming the y axis
plt.ylabel('ochered - axis')
plt.show()