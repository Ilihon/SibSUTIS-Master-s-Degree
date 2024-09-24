#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <queue>
using namespace std;
const int N = 11;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int tc, ar = 500000;
	int buf[N+1] = {0};
	int Conv[N] = {0};
	bool f = true;
	for(tc = 0; f ; ++tc){
		if(buf[0] == 0 && ar > 0){
			buf[0] = 6 + rand()%5;
			--ar;
		}
		for(int i = 0; i < N; ++i){
			if(buf[i] != 0 && Conv[i] == 0){
				Conv[i] = buf[i];
				buf[i] = 0;	
				--Conv[i];
			} else if(Conv[i] != 0){
				--Conv[i];
				if(Conv[i] == 0){
					buf[i+1] = 6 + rand()%5;
				}
			} 	
		}
		if(ar == 0){
			for(int i = 0; i < N; ++i){
				if(Conv[i] != 0 ){
					f = true; 	
					break;
				} else {
					f = false;
				}
			}
		}
	}
	cout<<" Тиков: "<<tc<<endl;
	return 0;
}

/// 0b - 0c / 1b - 0c - 1c/ 2b - 1c - 2c/ 3b - 2c - 3c/ 4b - 3c - 4c
