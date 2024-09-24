#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 100;

struct Coords{int x; int y;
friend bool operator==(const Coords& a, const Coords& b);} T;

bool operator==(const Coords& a, const Coords& b)
{
	return a.x == b.x && a.y == b.y;
}

float distance(Coords T1, Coords T2){
	return sqrt(pow((T1.x-T2.x),2)+pow((T1.y-T2.y),2));
	
}
int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	unsigned int t1, t2;
	int l;
	float min = 0;
	float summ = 0;
	cout<<endl<<" ¬ведите кол-во точек: ";
	cin>>l;
	t1 = clock();
	vector<Coords> c(l);
	int *I, *R;
	I = new int[l-1];
	R = new int[l-1];
	for(int i = 0; i < l - 1; ++i){
		I[i] = i + 1;
	}
	for(int i = 0; i < l; ++i){
		T.x = rand()%100;
		T.y = rand()%100;
		vector<Coords>::iterator p;
  		p = std::find (c.begin(), c.end(), T);
  		for (;p != c.end();){
  			T.x = rand()%100;
			T.y = rand()%100;
			p = find (c.begin(), c.end(), T);
		}
		c[i] = T;	
	}
	
	for(int i = 0; i < l-1; ++i){
		R[i] = I[i];
		if(i!=l-2){
			summ += distance(c[I[i]],c[I[i+1]]);
		}	
	}
	summ += distance(c[0],c[I[0]]);
	summ += distance(c[0],c[I[l-2]]);
	//cout<<"summ0 = "<<summ<<endl;
	min = summ;
	for(;next_permutation(I,I+l-1);){
		summ = 0;
		for(int i = 0; i < l-1; ++i)
			if(i!=l-2)
				summ += distance(c[I[i]],c[I[i+1]]);	
		summ += distance(c[0],c[I[0]]);
		summ += distance(c[0],c[I[l-2]]);
		//cout<<"summ = "<<summ<<endl;
		if(summ<min){
			min = summ;
			for(int i = 0; i < l-1; ++i){
				R[i] = I[i];
				//cout<<" "<<R[i]<<" ";
		    }
		}
	}
	cout<<endl;
	for(int i = 0; i < l-1; ++i){
		cout<<" "<<R[i]<<" ";
	}
	cout<<endl;
	/*for(int i = 0; i < l; ++i){
		cout<<" "<<c[i].x<<" "<<c[i].y<<endl;
	}*/
	cout<<"min = "<<min<<endl;
	t2 = clock() - t1;
	cout<<"time = "<<t2<<endl;
	return 0;
}
