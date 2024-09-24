#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>

using namespace std;
int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string alp = "ÀÁÂÃÄÅ¨ÆÇÈ";
	string b1 = "";
	string b2 = "";
	string b3 = "";
	int f,a,b,c,d;
	bool f1,f2,f3,f4;
	f1 = f2 = f3 = f4 = 0;
	a = b = c = d = 0;
	int p[4] = {0,0,0,0};
	srand(time(0));
	for(;f1 == false || f2 == false || f3 == false || f4 == false;){
		f = rand()%4;
		switch(f){
			case 0:
				if(a > 9){
					p[0] = 0;
					f1 = true;
					break;	
				}
				else{
					if(p[0] == 0){
						p[0] = 2;
					}
					if(p[3] == 1){
						break;
					}
					b1 += alp[a];
					++a;
				}
					
			break;
			case 1:
				if(b > 9){
					p[1] = 0;
					f2 = true;
					break;
				}
				else{
					if(p[1] == 0){
							p[1] = 2;
					}
					if(p[3] == 1){
						break;
					}
					if(alp[b] == 'À' || alp[b] == '¨' || alp[b] == 'Å' || alp[b] == 'È' || alp[b] == '*'){
						b2 += alp[b];
						++b;
					}
					else{
						++b;
					}
					
				}
			break;
			case 2:
				if(c > 9){
					p[2] = 0;
					f3 = true;
					break;
				}
				else{
					if(p[2] == 0){
							p[2] = 2;
					}
					if(p[3] == 1){
						break;
					}
					
					if(alp[c] != 'À' && alp[c] != '¨' && alp[c] != 'Å' && alp[c] != 'È' || alp[c] == '*'){
						b3 += alp[c];
						++c;
					}
					else{
						++c;
					}
					
				}
			break;
			case 3:
				if(d > 9){
					p[3] = 0;
					f4 = true;
					break;
				}
				else{
					if(p[3] == 0){
						if(p[0] == 0){
							a = 10;
						}
						if(p[1] == 0){
							b = 10;
						}
						if(p[2] == 0){
							c = 10;
						}
						p[3] = 1;
						
					}
					alp[d] = '*';
					++d;
					
										
				}
			break;
		}
	}
	cout<<endl<<b1<<endl<<b2<<endl<<b3<<endl<<alp<<endl;
	return 0;
}
