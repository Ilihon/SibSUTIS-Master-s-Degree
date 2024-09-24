import random as rnd
import matplotlib.pyplot as plt
prior1=4
prior2=1
prior3=1
prior4=1
p1=prior1/(prior1+prior2+prior3+prior4)
p2=prior2/(prior1+prior2+prior3+prior4)
p3=prior3/(prior1+prior2+prior3+prior4)
p4=prior4/(prior1+prior2+prior3+prior4)

f = open("D://pythonLABS//lab3.txt", "w+")
f.truncate(0)
f.close()
readpos=0
num=0
x = []
y = []
for prior in range(30):
    prior1=prior
    prior2=1
    prior3=1
    prior4=1
    p1=prior1/(prior1+prior2+prior3+prior4)
    p2=prior2/(prior1+prior2+prior3+prior4)
    p3=prior3/(prior1+prior2+prior3+prior4)
    p4=prior4/(prior1+prior2+prior3+prior4)
    num=0
    for i in range(1000):
        choose=rnd.random()
        if(p1>choose):
            f = open("D://pythonLABS//lab3.txt", "a")
            f.write("a")
            f.close()
        elif(p1+p2>choose):
            f = open("D://pythonLABS//lab3.txt", "a")
            f.write("b")
            f.close()
        elif(p1+p2+p3>choose):
            f = open("D://pythonLABS//lab3.txt", "r")
            #c=f.read(readpos)
            f.close()
            #print(c)
            readpos+=1
            num+=1
        elif(p1+p2+p3+p4>choose):
            f = open("D://pythonLABS//lab3.txt", "r")
            #c=f.read(readpos)
            f.close()
            #print(c)
            readpos+=1
    print(prior, num)
    x.append(prior)
    y.append(num)    
plt.xlabel('x - prior read')
# naming the y axis
plt.ylabel('y - write symbols')
plt.plot(x, y)
plt.show()
f.close()