#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <math.h>
#include <queue>
#include <algorithm>
#include <graphics.h>
//using namespace std;



static const int N = 1024;

double distance(double x, double y){
    
    double a = 0.6;
    double b = 0.5;
    double c = 0.3;

    double x0 = 0.2;
    double y0 = -0.3;
    double z0 = 0.8;

    double mu = 1.0;
    double I0 = 1.0;

    double sourse_x = 0.0;
    double sourse_y = 0.0;
    double sourse_z = 5.0;

    double sensor_x = 0.0;
    double sensor_y = 0.0;
    double sensor_z = 0.0;
    
	double z = 0;
	double m = sourse_x-x;
	double p = sourse_y-y;
	double n = sourse_z-z;
	double A = pow(m,2) * pow(b,2) * pow(c,2) + pow(p, 2)*pow(a,2)*pow(c,2) + pow(n,2)*pow(a,2)*pow(b,2);
	double B = 2*(m * (sourse_x-x0) * pow(b,2) * pow(c,2) + p * (sourse_y-y0)*pow(a,2)*pow(c,2) + n * (sourse_z-z0)*pow(a,2)*pow(b,2));
	double C = pow((sourse_x-x0),2) * pow(b,2) * pow(c,2) + pow((sourse_y-y0),2) * pow(a,2) * pow(c,2) + pow((sourse_z-z0),2) * pow(a,2) * pow(b,2) - pow(a,2) * pow(b,2) * pow(c,2);
	double D;
	double t1, t2;
	double res[6];
	D = pow(B,2) - 4*A*C;
	if(D <= 0.0){
		return 0.0;
	} else{
		t1 = (-B + sqrt(D))/(2*A);
		t2 = (-B - sqrt(D))/(2*A);
	
		res[0] = sourse_x + m*t1;
		res[1] = sourse_y + n*t1;
		res[2] = sourse_z + p*t1;
	
		res[3] = sourse_x + m*t2;
		res[4] = sourse_y + n*t2;
		res[5] = sourse_z + p*t2;
			
		return (sqrt(pow((res[3] - res[0]),2) + pow((res[4] - res[1]),2) + pow((res[5] - res[2]),2)));
	}
	
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	double **Sensor = new double *[N];
	for(int i = 0; i < N; ++i){
		Sensor[i] = new double[N];
	}
	double x, y, dx, dy,r;
	x = y = -1.0;
	dx = (double)2/N ;
	dy = (double)2/N ;
	
	for(int i = 0; i < N; ++i, x +=dx){
		for(int j = 0; j < N; ++j, y += dy){
			r = distance(x, y);
			if(r == 0.0){
				Sensor[i][j] = 1.0;
			} else{  
				Sensor[i][j] = exp(-r);
			}
		}
		y = -1;
	}
	
	
	/*
	for(int i = 0; i < N; ++i){
		std::cout<<endl;
		system("pause");
		for(int j = 0; j < N; ++j)
			std::cout<<Sensor[i][j]<<" ";
	} 
	*/
	initwindow(1024,1024); 
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
            if(Sensor[i][j] == 1.0){
				putpixel (i, j, 0);
			} else{
				putpixel (i, j, RGB(int(Sensor[i][j]*256),int(Sensor[i][j]*256),int(Sensor[i][j]*256)));
			}    
        }
	} 
    
           
    getch();             
    closegraph();
	for(int i = 0; i < N; ++i){
		delete [] Sensor[i];
	}
	return 0;
}
