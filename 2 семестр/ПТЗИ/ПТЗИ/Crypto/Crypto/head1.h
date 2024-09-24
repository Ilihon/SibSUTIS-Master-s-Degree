#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdint.h>
#include <math.h>
#include <fstream>
#include <time.h>
#include <limits.h>
#include <string>
#define ll _int64
using namespace std;

struct key
{
  ll d; 
  ll k;
};
//cd c:\users\npuma94\desktop\Защита информаци

void myqsort(struct key A[],ll l, ll r)
{
  ll i=l, j =r;
  ll p;
  struct key temp;
  p = A[l].d;
  //printf(" %d\n", p);
  for(;i<=j;)
  {
    for(;A[i].d < p; ++i){}
    for(;A[j].d > p; --j){}
    if (i <= j)
    {
      temp.d = A[i].d;
      temp.k = A[i].k;
      A[i].d = A[j].d;
      A[i].k = A[j].k;
      A[j].d = temp.d;
      A[j].k = temp.k;
      ++i; --j;

    }
      
  }
  if(j > l) myqsort(A,l, j);
  if(i < r) myqsort(A,i, r);
} 
  /*template<typename T>
  int qscomp(const void *x1, const void *x2)
  {
      struct key a = x1;
      struct key b = x2;
      return ( a.p - b.p); 

  } */
ll BS (struct key A[], ll n, ll k)
{
    ll l = 0, r = n, m;
    
    for(;l<=r;)
    {
        m = l + (r - l)/2;
        if (k<A[m].d) r=m-1;
          else if (k>A[m].d) l=m+1;
        else return A[m].k;
    }
    return -1;
}
void Evklid(ll a, ll b, ll *D)
{
    const int n = 3;
    ll q=0;
    ll U[n]={a,1,0}, V[n]={b,0,1}, T[n]={0,0,0};
    for(;U[0]%V[0]!=0;)
	{
		q = U[0] / V[0];
		T[0]= U[0]%V[0];
       
		T[1]= U[1]-q*V[1];
		T[2]= U[2]-q*V[2];
		for(int j =0; j<n; ++j)
		{
			U[j]=V[j];
            V[j]=T[j];
		}
    }
	D[0] = T[0], D[1] = T[1], D[2] = T[2]; //эвклида доработать, 3 возвращать
}
ll Fpow (ll a, ll x, ll o ){
  ll y = 1, s = a;
  for(int i = 0; (x>>i)!=0 ; ++i){
      if((x>>i) & 1)
        y=(y*s)%o;
      s=(s*s)%o;
  }
  return y;
}
bool simp(ll x)
{
  ll n =(ll)sqrt(x);
  bool f = 1;
  for(int i = 2; i <= n; ++i)
  {

    if((x%i) == 0)
    {
        f = 0;
        i = n;
    }
  }
  return f;
}
void mr(ll &x)
{
    x=rand()%USHRT_MAX*rand()%INT_MAX/101 + rand()%INT_MAX;
}
void rus(ll &x)
{
	x = rand() % USHRT_MAX + 3733;
}
void rin(ll &x)
{
	x = rand() % INT32_MAX + rand() % INT32_MAX;
}
void rdh(ll &x, ll &y)
{
	ll q = 0, p = 0, g = 0;
	mr(q);
	p = q * 2 + 1;
	for (;!(simp(q) && simp(p));)
	{
		mr(q);
		p = q * 2 + 1;
	}
	mr(g);
	for (;!(Fpow(g, q, p) != 1) || g<2 || g>(p-1);)
		mr(g);
	x = p;
	y = g;
}
void r15(ll &x)
{
	x = rand() % 0x4000 + 0x4000;
}
void r16(ll &x)
{
	x = rand() % 0x8000 + 0x8000;
}
void DH(){
  ll q=0,p=0,g=0,x1,x2,y1,y2,z1,z2;
  mr(q);
  p = q*2 + 1;
  for(;!(simp(q) && simp(p));)
  {
      mr(q);
      p = q*2 + 1;
  }
  mr(g);
  for(;!(Fpow(g,q,p)!=1);)
    mr(g); 
    
  mr(x1),mr(x2);
  y1 = Fpow(g,x1,p);
  y2 = Fpow(g,x2,p);
  z1 = Fpow(y2,x1,p);
  z2 = Fpow(y1,x2,p); 
  /*cout<<simp(g)<<" "<<simp(q)<<" "<<simp(p)<<endl;
  cout<<Fpow(g,q,p)<<endl;
  cout<<"g = "<<g<<" "<<"q = "<<q<<" "<<"p = "<<p<<" "<<"Xa = "<<x1<<" "<<"Xb = "<<x2<<" "<<endl;
  cout<<"Ya = g^Xa%p = "<<g<<"^"<<x1<<"%"<<p<<" = "<<y1<<endl<<"Yb = g^Xb%p = "<<g<<"^"<<x2<<"%"<<p<<" = "<<y2<<endl;
  cout<<"Zab = Yb^Xa%p = "<<y2<<"^"<<x1<<"%"<<p<<" = "<<z1<<endl<<"Zba = Ya^Xb%p = "<<y1<<"^"<<x2<<"%"<<p<<" = "<<z2<<endl;*/
  if (z1 == z2)
    cout<<"Zab = Zba:"<<z1<<" = "<<z2<<endl;
  else 
    cout<<"oooops, overload"<<endl;
}
ll LBStep(ll a, ll y, ll p){
  ll m,k;
  m = k = sqrt(p) + 1;
  ll *M = new ll [m];
  struct key *K = new struct key [k];
  for(int i = 0; i < k; ++i)
  {
    K[i].d = 0;
    K[i].k = i;
  }
  for(int i = 0; i < m; ++i)
    M[i] = (y*Fpow(a,i,p))%p;
  for(int i = 1; i <= k; ++i)
    K[i-1].d = Fpow(a,(i*m),p);
  for(int i = 0; i < m; ++i)
    cout<<M[i]<<" - "<<i<<endl;
  cout<<endl;
  myqsort(K,0,k-1);
  for(int i = 0; i < k; ++i)
    cout<<K[i].d<<" - "<<K[i].k<<endl;
  for(int i = 0; i < m; ++i)
  {
      if(BS(K,k,M[i])!=-1)
      {
          ll tmp = (BS(K,k,M[i]) + 1)*m - i;
          delete [] M;
          delete [] K;
          return (tmp);
      }
  }

  delete [] M;
  delete [] K;
  return -1;
}