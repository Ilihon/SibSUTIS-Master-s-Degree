#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	double tau = 0.1;
	double lambda;
	double mu;
	double t = 0.1;
	int p, p1,queue = 0;
	bool qs = false;
	
	char fn[20];
	cout<<"Введите плотность заявок: ";
	cin>>lambda;
	cout<<endl;
	cout<<"Введите интенсивность обработки: ";
	cin>>mu;
	cout<<endl;
	sprintf(fn, "%f%s", lambda/mu, ".csv");
	cout<<fn<<endl;
	FILE *out = fopen(fn,"w");
	for(int i = 0; i < 20000; ++i){
		p = int(exp(-lambda*tau)*100);
		//cout<<" вер не прихода: "<<p<<endl;
		p1 = 1 + rand()%100;
		if(p1 <= p){
			tau+=0.1;
			//cout<<" не пришла: "<<p1<<endl;
		} else{
			//cout<<" пришла: "<<p1<<endl;
			tau = 0.1;
			if(qs){
				++queue;			
			} else{
				qs = true;
			}
		}
		if(qs){
			p = int(exp(-mu*t)*100);	
			//cout<<" вер не обработки: "<<p<<endl;
			p1 = 1 + rand()%100;
			if(p1 <= p){
				t+=0.1;
				//cout<<" не обработалась: "<<p1<<endl;
			} else{
				//cout<<" обработалась: "<<p1<<endl;
				t = 0.1;
				if(queue > 0){
					--queue;			
				} else{
					qs = false;
				}
			}
		}
		fprintf(out, "%d;%d\n", i, queue);
		
		//cout<<" t: "<<t<<" tau: "<<tau<<" qs: "<<qs<<" qeue: "<<queue<<endl;
	}
	fclose(out);
	cout<<" qeue: "<<queue<<endl;
	return 0;
}
