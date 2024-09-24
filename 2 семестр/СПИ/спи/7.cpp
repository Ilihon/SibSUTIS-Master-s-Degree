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
	double lambda = 1;
	double mu;
	double t = 0.1;
	int p, p1,queue = 0,N = 0,N0 = 0,N1 = 0, L = 10;
	bool qs = false;
	double C1 = 1, C2 = 0.3, C3 = 0.2, E;
	char fn[20];
	
	for(mu = 1.5; mu > 0.4; mu-=0.1){
		
		for(int i = 0; i < 100000; ++i){
			p = int(exp(-lambda*tau)*100);
			//cout<<" вер не прихода: "<<p<<endl;
			p1 = 1 + rand()%100;
			if(p1 <= p){
				tau+=0.1;
				//cout<<" не пришла: "<<p1<<endl;
			} else{
				++N;
				//cout<<" пришла: "<<p1<<endl;
				tau = 0.1;
				if(qs){
					if(queue < 10){
						++queue;
						++N1;
					} else{
						++N0;
					}			
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
			//cout<<" t: "<<t<<" tau: "<<tau<<" qs: "<<qs<<" qeue: "<<queue<<endl;
		}
		N1/=1000;
		E = N*C1 - C2*N0 - C3*N1;
		N = 0, N0 = 0, N1 = 0;
		cout<<" Mu: "<<mu<<" E: "<<E<<endl;	
	}
	
	
	return 0;
}
