#include "stdafx.h"
//#include <math.h>
#include "Crypto.h"
//using namespace std;
long long fast(long long a, long long b, long long n)
{
	long long s = 1;
	/*vector <int> A;
    int i=0;
    
	for(i=0;i<3;i++){
	  A[i]=b%2;
	   cout<<A[i]<<endl;
	  }
	 
	  i=0;*/
	while (b)
	{
		if (b & 1)
			s = (s*a) % n;
		b>>=1;
		a = (a*a) % n;
	}
	return s;
}
bool Simple(long long A)
{
	long long a = sqrt(A);
	
	for (int i = 2; i <= a; i++)
	{
		
		if (A%i == 0)
			return false;
	}
	return true;
}
/*long int Evklid(long long a, long long b,long long *B)
{
	
	const int n = 3;
	long int q = 0;
	int i;
	long long U[n], V[n], T[n];

	U[0] = a; U[1] = 1; U[2] = 0;
	V[0] = b; V[1] = 0; V[2] = 1;
	T[0] = 0; T[1] = 0; T[2] = 0;

	while (U[0] % V[0] != 0)
	{
		T[0] = U[0] % V[0];
		q = U[0] / V[0];
		T[1] = U[1] - q*V[1];
		T[2] = U[2] - q*V[2];
    for(int j =0; j<n; j++){
            U[j]=V[j];
            V[j]=T[j];
            }
    
   }
	for(i=0;i<n;i++)
	B[i]=T[i];
}*/
long long PRSA(string fl){
     long long P=0,Q=0,C=0,D=0,N=0,fi=0,J[3]={},s,y=13,w,i;
	 string str = "";
	 CompHash(fl, str);
     	P =  rand();
        Q = rand();
     while(!Simple(P)|| !Simple(Q))
	{
		P =  rand();
        Q =  rand();
	} 
	 cout << "P "<< P << endl;
     cout << "Q "<< Q << endl;
     N=P*Q;
     fi=(P-1)*(Q-1);
     D=rand();
     Evklid(fi,D,J);
     while(D>fi  || J[0]!=1 ){
        D= rand()*rand() + rand();
        Evklid(fi,D,J);
     }
     C=J[2];
     if (C<0)
        C+=fi;
     cout <<"D "<< D << endl;
     cout <<"C "<< C << endl;
	 ofstream out3("K.txt", ios::binary | ios::out);
	 out3.write((char *)&C, sizeof(long long));
	 out3.write((char *)&N, sizeof(long long));
	 out3.write((char *)&D, sizeof(long long));
	 out3.close();

	 ifstream fin1("K.txt", ios::binary | ios::in);
	 ofstream out("1.txt", ios::binary | ios::out);
	 ofstream out1("2.txt", ios::binary | ios::out);
	 fin1.read((char *)&C, sizeof(ll));
	 fin1.read((char *)&N, sizeof(ll));
	 fin1.read((char *)&D, sizeof(ll));
	 fin1.close();
	 for (int i = 0; i < str.length();++i)
	 {
		 
		 
		 s = fast(str[i], C, N);
		 w = fast(s, D, N);
		 out.write((char *)&w, sizeof(char));
		 out1.write((char *)&str[i], sizeof(char));

	 }
	 fin1.close();
	 out.close();
	 out1.close();
	 cout << "s " << s << endl;
	 cout << "w " << w << endl;
	 return w;
     }
long long PEG(string fl){
     long long r,p,x,y,h=3,k,u,q,g,s,J[3]={},C;
	 unsigned char t,v;
	 string str = "";
	 CompHash(fl, str);
	 ofstream out1("DS.txt", ios::binary | ios::out);
	 ofstream out2("K.txt", ios::binary | ios::out);
     q = rand()*rand() +  rand();
     p =  2*q+1;
        while(!Simple(p) || !Simple(q))
	{
        q = rand()*rand() +  rand();
       	p = 2*q+1;
       
	} 
  g = rand() % 100;
  for (;fast(g, q, p) != 1;)
	  g = rand() % 100;
	  
  cout << "q " << q << endl;
   cout << "p " << p << endl;
   cout << "g " << g << endl;

  x=rand()*rand() + rand();
  for(;x<1 || x>p-1;)
      x=rand()*rand() + rand();
      cout << "x " << x << endl;
      
  y=fast(g,x,p);
  
   cout << "y " << y << endl;
 
        //cout << "C " << C << endl;
  // r=fast(g,k,p);
//    cout << "r " << r << endl;
	for (int i = 0; i < str.length();++i)
	{
		k = rand()*rand() + rand();
		Evklid(p - 1, k, J);
		while (k<1 || k>p - 1 || J[0] != 1) {
			k = rand()*rand() + rand();
			Evklid(p - 1, k, J);
		}

		C = J[2];
		if (C < 0)
			C += p - 1;

		r = fast(g, k, p);

		u = (str[i] - x*r) % (p - 1);
		if (u < 0)
			u += p - 1;
		//cout << "u " << u << endl;

		s = C*u % (p - 1);
		out1.write((char *)&r, sizeof(long long));
		out1.write((char *)&s, sizeof(long long));
		out2.write((char *)&p, sizeof(long long));
		out2.write((char *)&y, sizeof(long long));
		out2.write((char *)&g, sizeof(long long));
		//cout << "s " << s << endl;
	}
	out1.close();
	out2.close();
	ifstream fin1("DS.txt",ios::binary|ios::in);
	ifstream fin2("K.txt", ios::binary | ios::in);
	ofstream out3("1.txt", ios::binary | ios::out);
	ofstream out4("2.txt", ios::binary | ios::out);
	for (int i = 0; i < str.length();++i)
	{
		fin1.read((char *)&r, sizeof(long long));
		fin1.read((char *)&s, sizeof(long long));
		fin2.read((char *)&p, sizeof(long long));
		fin2.read((char *)&y, sizeof(long long));
		fin2.read((char *)&g, sizeof(long long));
		t = (fast(y, r, p)* fast(r, s, p)) % p;
		out3.write((char *)&t,sizeof(t));
		//cout << "t " << t << endl;
		v = fast(g, str[i], p);
		out4.write((char *)&v, sizeof(v));

	}
	fin1.close();
	fin2.close();
	out3.close();
	out4.close();
	cout << "t " << t << endl;
   cout << "v " << v << endl;
   return v;
  
}
long long GOST(string fl)
{    
     srand(time(NULL));
     long long p,q,b,a,y,x,h,k,r=0,s=0,J[3]={},u1,u2,v,C,n,i;
	 string str = "";
	 CompHash(fl, str);
	 
     q=rand() % 0x4000 + 0x4000;
     b=rand() % 0x8000 + 0x8000;
	 p = b*q + 1;
     while(!Simple(q) || !Simple(p) || !p >> 31 & 1){
          q=rand() % 0x4000 + 0x4000;
          b=rand() % 0x8000 + 0x8000;
          p=b*q+1;
     }
     
     
    // cout << "p " << p << endl;
     //cout << "q " << q << endl;
     //cout << "b " << b << endl;
     
     n=rand()*rand()+rand();
     a=fast(n,b,p);
     //cout << "a " << a << endl;
     while(a==1){
          n=rand()*rand()+rand();
          a=fast(n,b,p);
          }
          
     //cout << "a " << fast(a,q,p) << endl;
          
     x=rand()*rand()+rand();
     while(x<0 || x>q)
          x=rand()*rand()+rand();
          
    // cout << "x " << x << endl;
     
     y=fast(a,x,p);
     
     //cout << "y " << y << endl;
     
     
     
    // cout << "k " << k << endl;
	 ofstream out1("DS.txt", ios::binary | ios::out);
	 ofstream out2("K.txt", ios::binary | ios::out);
     
	 for (int i = 0; i < str.length();++i)
	 {
		 k = rand()*rand() + rand();
		 r = 0, s = 0;
		 while (r == 0 || s == 0) 
		 {
			 while (k<0 || k>q)
				 k = rand()*rand() + rand();
			 r = (fast(a, k, p)) % q;
			 s = (k*str[i] + x*r) % q;
		 }

		 out1.write((char *)&r, sizeof(ll));
		 out1.write((char *)&s, sizeof(ll));
		 out2.write((char *)&p, sizeof(ll));
		 out2.write((char *)&q, sizeof(ll));
		 out2.write((char *)&k, sizeof(ll));
		 out2.write((char *)&a, sizeof(ll));
		 out2.write((char *)&y, sizeof(ll));
		 
	 }
	 out1.close();
	 out2.close();
	 ifstream fin1("DS.txt", ios::binary | ios::in);
	 ifstream fin2("K.txt", ios::binary | ios::in);
	 for (int i = 0; i < str.length();++i)
	 {
		 fin1.read((char *)&r, sizeof(ll));
		 fin1.read((char *)&s, sizeof(ll));
		 fin2.read((char *)&p, sizeof(ll));
		 fin2.read((char *)&q, sizeof(ll));
		 fin2.read((char *)&k, sizeof(ll));
		 fin2.read((char *)&a, sizeof(ll));
		 fin2.read((char *)&y, sizeof(ll));
		 Evklid(q, str[i], J);
		 C = J[2];
		 if (C < 0) C += q;

		 u1 = (s*C) % q;
		 
		 u2 = ((-r)*C) % q;
		 u2 = q + u2;
		

		 v = ((fast(a, u1, p)*fast(y, u2, p)) % p) % q;
		 if (v != r)
		 {
			 cout << "fake Signature";
				 i = str.length();
		 }
		 else cout << " r = " << r << " v = " << v << endl;
		
	 }
	 fin1.close();
	 fin2.close();
	 return v;
}

int main(){
    
    PRSA("1.txt");
    //PEG("1.txt");
    //GOST("1.txt");
    system("PAUSE");
    return 0;
    
    }
