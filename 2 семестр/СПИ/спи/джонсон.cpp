#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;
struct details{int x; int y;
friend bool operator==(const details& a, const details& b);} T;
bool operator==(const details& a, const details& b)
{
	return a.x == b.x && a.y == b.y;
}
int maxb(vector<int> &sumb){
	int max = 0;
	for(int i = 0; i < sumb.size(); ++i){
		if(sumb[i] > max){
			max = sumb[i];
		}
	}
	return max;
}
int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int l;
	float summ = 0;
	float min = 0;
	unsigned int time;
	cout<<endl<<" ¬ведите кол-во деталей: ";
	cin>>l;
	vector<details> c(l);
	vector<int> sumb(l);
	int *I, *R;
	I = new int[l];
	R = new int[l];
	for(int i = 0; i < l; ++i){
		I[i] = i;
	}
	for(int i = 0; i < l; ++i){
		T.x = 5 + rand()%11;
		T.y = 5 + rand()%11;
		c[i] = T;	
	}
	for(int i = 0; i < l; ++i){
		cout<<endl<<c[i].x<<" "<<c[i].y<<endl;	
	}
	cout<<endl<<endl;
	time = clock();	
	for(int i = 0; i < l; ++i){
		R[i] = I[i];
		summ += c[I[i]].y;	
		for(int j = 0; j <= i; ++j){
			if(j!=0){
				sumb[i] += c[I[j]].x - c[I[j-1]].y;
			} else{
				sumb[i] += c[I[j]].x;
			}
		}
	}
	summ+=maxb(sumb);
	cout<<endl<<"summ0 = "<<summ<<endl;
	min = summ;
	for(;next_permutation(I,I+l-1);){
		summ = 0;
		memset(&sumb[0], 0, sizeof(int)*sumb.size());
		for(int i = 0; i < l; ++i){
			summ += c[I[i]].y;
			for(int j = 0; j <= i; ++j){
				if(j!=0){
					sumb[i] += c[I[j]].x - c[I[j-1]].y;
				} else{
					sumb[i] += c[I[j]].x;
				}
			}
		}
		summ+=maxb(sumb);
		if(summ<min){
			min = summ;
			for(int i = 0; i < l; ++i){
				R[i] = I[i];
		    }
		}
	}
	time = clock() - time;
	cout<<endl<<"optimal order: "<<endl;
	for(int i = 0; i < l; ++i){
		cout<<endl<<R[i]<<endl;	
	}
	cout<<endl<<"final summ = "<<min<<endl;
	cout<<endl<<"time = "<<time<<endl;
	return 0;
}
