#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <queue>
using namespace std;


int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	string alp = "АБВГДЕЁЖЗИ";
	queue<int> r,w;
	int cr, cw;
	cr = cw = 0;
	int ar = -1;
	int aw = -1;
	for(int i; i < 100000; ++i){
		int c = rand()%1000;
		if (c < 5){
			if(aw == -1 && ar == -1){
				aw = 0;
			} else{
				w.push(i);
			}
		} else if(c>=5 && c < 55){
			if(ar == -1 && aw == -1){
				ar = 0;
			} else{
				r.push(i);
			}
		}
		/*if(aw >= 0){
			++aw;
			if (aw == 100){
				++cw;
				if(!w.empty()){
					aw = 0;
					w.pop();	
				} else{
					aw = -1;
				}
				
			}
		} else if(ar >= 0) {
			++ar;
			if (ar == 10){
				++cr;
				if(!r.empty()){
					ar = 0;
					r.pop();	
				} else{
					ar = -1;
				}
				
			}
		}*/
		if(ar >= 0) {
			++ar;
			if (ar == 10){
				++cr;
				if(!r.empty()){
					ar = 0;
					r.pop();	
				} else{
					ar = -1;
				}
				
			}
		} else if(aw >= 0){
			++aw;
			if (aw == 100){
				++cw;
				if(!w.empty()){
					aw = 0;
					w.pop();	
				} else{
					aw = -1;
				}
				
			}
		} 
	}
	cout<<" Записи: "<<cw<<endl<< " Чтения: "<<cr<<endl;
	cout<<" Осталось записи: "<<w.size()<<endl<< " Осталось чтения: "<<r.size()<<endl;
	return 0;
}
