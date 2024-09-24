#pragma once
#include "head1.h"
#include "..\cryptopp562\sha3.h"
#include "..\cryptopp562\cryptlib.h"
#include "..\cryptopp562\hex.h"
int sw = 0;

void RSA(char m, ll &c, ll &v, ll &n)
{
	ll P1=0, Q1, N1, F1, C1, D1;
	ll A[3] = {};
	rus(P1);
	rus(Q1);
	for (;!simp(P1);)
		rus(P1);
	for (;!(simp(Q1) && (P1 != Q1));)
		rus(Q1);
	N1 = P1*Q1;
	F1 = (P1 - 1)*(Q1 - 1);
	rin(D1);
	Evklid(F1,D1,A);
	for (;(D1 >= F1) || (A[0] != 1);)
	{
		rin(D1);
		Evklid(F1, D1, A);
	}
	C1 = A[2];
	if (C1 < 0)
		C1 += F1;
	c = C1;
	//v = Fpow(m, D1, N1);
	v = D1;
	n = N1;
}
void Sha(ll m)
{
	ll P, C1, C2, D1, D2, X1,X2,X3,X4;
	ll B[3] = {};
	mr(P);
	for (;!simp(P);)
		mr(P);
	rus(D1);
	rus(D2);
	Evklid((P-1), D1, B);
	for (;(D1 >= (P-1) || (B[0] != 1));)
	{
		rus(D1);
		Evklid((P - 1), D1, B);
	}
	C1 = B[2];
	if (C1 < 0)
		C1 += (P-1);
	B[0] = 0;
	Evklid((P - 1), D2, B);
	for (;(D2 >= (P - 1) || (B[0] != 1));)
	{
		rus(D2);
		Evklid((P - 1), D2, B);
	}
	C2 = B[2];
	if (C2 < 0)
		C2 += (P - 1);
	cout << " c1 " << C1 << " d1 " << D1 << " p" << P << endl;
	X1 = Fpow(m, C1, P);
	X2 = Fpow(X1, C2, P);
	X3 = Fpow(X2, D1, P);
	X4 = Fpow(X3, D2, P);
	cout << m << " " << X4 << endl;
}
void ElGamal(unsigned char m, ll &r, ll &e, ll &x, ll &y, ll &g, ll &p)
{
	ll k;
	if (p == 0)
	{
		rdh(p,g);
		rus(x);
		y = Fpow(g,x,p);
	}
	mr(k);
	for (;!(k>1 && k<(p-1));)
		mr(k);
	r = Fpow(g,k,p);
	e = (m*Fpow(y, k, p)) % p;
}
void FileEnc(string flnm)
{
	ll key=0, e=0, p=0,r=0,x=0,y=0,g=0;
	
	unsigned char c, m;
	ifstream fin(flnm, ios::binary | ios::in);
	ofstream out1("code.bmp", ios::binary | ios::out);
	ofstream out2("key.bmp", ios::binary | ios::out);
	if (!fin) cout << "error1";
	if (!out1) cout << "error2";
	if (!out2) cout << "error3";
	for (; !fin.eof();)
	{

		switch (sw) 
		{
		case 1: 
		{
			fin.read((char *)&c, sizeof(char));
			RSA(c, key, e, p);
			out1.write((char *)&e, sizeof(ll));
			out2.write((char *)&key, sizeof(ll));
			out2.write((char *)&p, sizeof(ll));
			break;
		}
		case 2: 
		{
			fin.read((char *)&c, sizeof(char));
			m = rand() % 256;
			c ^= m;
			out1.write((char *)&c, sizeof(char));
			out2.write((char *)&m, sizeof(char));
			break;
		}
		case 3: 
		{
			
			fin.read((char *)&c, sizeof(char));
			ElGamal(c, r, e, x, y, g, p);
			out1.write((char *)&r, sizeof(ll));
			out1.write((char *)&e, sizeof(ll));
			out2.write((char *)&p, sizeof(ll));
			out2.write((char *)&x, sizeof(ll));

			break;
		}
		default: 
			cout << "Incorrect input" << endl;
		}
	}
	fin.close();
	out1.close();
	out2.close();
}
void FileDec()
{

	ll a, x, p, l,r,e;
	char c, m;
	ifstream fin1("code.bmp", ios::binary | ios::in);
	ifstream fin2("key.bmp", ios::binary | ios::in);
	ofstream out("encoded.bmp", ios::binary | ios::out);
	if (!fin1) cout << "error1";
	if (!fin2) cout << "error2";
	if (!out) cout << "error3";
	for (; !fin1.eof();)
	{


		switch (sw) // начало оператора switch
		{
		case 1:
		{
			fin1.read((char *)&a, sizeof(ll));
			fin2.read((char *)&x, sizeof(ll));
			fin2.read((char *)&p, sizeof(ll));
			l = Fpow(a, x, p);
			out.write((char *)&l, sizeof(char));
			break;
		}
		case 2:
		{
			fin1.read((char *)&c, sizeof(char));
			fin2.read((char *)&m, sizeof(char));
			c ^= m;
			out.write((char *)&c, sizeof(char));
			break;
		}
		case 3:
		{
			fin1.read((char *)&r, sizeof(ll));
			fin1.read((char *)&e, sizeof(ll));
			fin2.read((char *)&p, sizeof(ll));
			fin2.read((char *)&x, sizeof(ll));
			c = (e * Fpow(r, (p - 1 - x), p)) % p;
			out.write((char *)&c, sizeof(char));
			break;
		}
		default:
			cout << "Incorrect input" << endl;
		}
		
	}
	fin1.close();
	fin2.close();
	out.close();
}
string Keccak(string data)
{
	byte const* pbData = (byte*)data.data();
	unsigned int nDataLen = data.size();
	byte abDigest[CryptoPP::SHA3_512::DIGESTSIZE];

	CryptoPP::SHA3_512().CalculateDigest(abDigest, pbData, nDataLen);
	CryptoPP::HexEncoder encoder;
	std::string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(abDigest, sizeof(abDigest));
	encoder.MessageEnd();
	return string(output);
}
void CompHash(string flnm, string &hs)
{
	
	char tmp;
	string hash="";
	ll n = 0;
	ifstream fin(flnm, ios::binary | ios::in);
	if (!fin) cout << "error1";
	fin.seekg(0, fin.end);
	n = fin.tellg();
	fin.seekg(0, fin.beg);
	char *T = new char[n+1];
	
	for (int i = 0; i < n; ++i)
		fin.read((char *)&T[i],sizeof(char));
	T[n] = '\0';
	fin.close();
	hs = Keccak(T);
	cout << " " << hs << " " << endl;
	delete[]T;
}
void EGDS(unsigned char m, ll &r, ll &s, ll &x, ll &y, ll &g, ll &p)
{
	ll k,k1,u;
	ll B[3] = {};
	if (p == 0)
	{
		rdh(p, g);
		rus(x);
		y = Fpow(g, x, p);
	}
	mr(k);
	Evklid((p-1),k,B);
	for (;k<2 || k>(p - 1) || B[0] != 1;)
	{
		mr(k);
		Evklid((p-1), k, B);
	}
	k1 = B[2];
		if(k1 < 0)
			k1+=(p-1);
	r = Fpow(g, k, p);
	u = (m - x*r) % (p - 1);
	if (u < 0)
		u += (p - 1);
	s = (k1*u) % (p - 1);
}
void Ghost(unsigned char m,ll &p,ll &q,ll &s,ll &r,ll &a, ll &k,ll &x,ll &y)
{
	ll b=0,g=0;
	if (p == 0)
	{
		r16(b);
		r15(q);
		p = b*q + 1;
		for (;!p >> 31 & 1 || !simp(p) || !simp(q);)
		{
			r16(b);
			r15(q);
			p = b*q + 1;
		}
		rus(g);
		a = Fpow(g, b, p);
		for (;a == 1;)
		{
			rus(g);
			a = Fpow(g, b, p);
		}
		rus(x);
		for (;x<1 || x>q;)
			rus(x);
		y = Fpow(a, x, p);
	}
	r = 0; s = 0;
	cout << q << endl;
	for (;!r || !s;)
	{
		rus(k);
		for (;k<1 || k>q;) {
			rus(k);
		}
		r = Fpow(a, k, p) % q;
		s = (k*m + x*r) % q;
	}

		
}
bool ChkG(unsigned char m, ll p, ll q, ll s, ll r, ll a, ll y)
{
	ll u1 = 0, u2 = 0, v = 0, A[3] = {},m1 = 0;
	Evklid(q, m, A);
	m1 = A[2];
	if (m1 < 0)
		m1 += q;
	u1 = s*m1%q;
	u2 = -r*m1%q;
	if (u2 < 0)
		u2 += q;
	v = ((Fpow(a, u1, p)*Fpow(y, u2, p) )% p) % q;
	cout << " v " << v << " r " << r << endl;
	if (v == r)
		return 1;
	else return 0;

}
void DigSig(string fl)
{

	ll key = 0, e = 0, p = 0, r = 0, x = 0, y = 0, g = 0,s = 0, q = 0, k = 0, a = 0;
	string str = "";
	CompHash(fl, str);
	unsigned char c, m;
	ofstream out1("DS.txt", ios::binary | ios::out);
	ofstream out2("K.txt", ios::binary | ios::out);
	if (!out1) cout << "error2";
	if (!out2) cout << "error3";
	for (int i = 0; i < str.length();++i)
	{

		switch (sw)
		{
		case 1:
		{

			RSA(str[i], key, e, p);
			out1.write((char *)&e, sizeof(ll));
			out2.write((char *)&key, sizeof(ll));
			out2.write((char *)&p, sizeof(ll));
			break;
		}
		case 2:
		{
			
			EGDS(str[i], r, s, x, y, g, p);
			out1.write((char *)&r, sizeof(ll));
			out1.write((char *)&s, sizeof(ll));
			out2.write((char *)&p, sizeof(ll));
			out2.write((char *)&y, sizeof(ll));
			out2.write((char *)&g, sizeof(ll));
			cout << " r " << r << " s " << s << " p " << p << " y " <<y<< endl;
			break;
		}
		case 3:
		{
			Ghost(str[i], p, q, s, r, a, k, x, y);
			out1.write((char *)&r, sizeof(ll));
			out1.write((char *)&s, sizeof(ll));
			out2.write((char *)&p, sizeof(ll));
			out2.write((char *)&q, sizeof(ll));
			out2.write((char *)&k, sizeof(ll));
			out2.write((char *)&a, sizeof(ll));
			out2.write((char *)&y, sizeof(ll));
			break;
		}
		default:
			cout << "Incorrect input" << endl;
		}
	}
	out1.close();
	out2.close();

}
void chkDigSig(string fl)
{

	ll a=0, x=0, p=0, l=0, r=0, e=0,s=0,y=0,g = 0,q = 0,k = 0;
	unsigned char c, m;
	bool f = true;
	string str = "";
	CompHash(fl, str);
	ifstream fin1("DS.txt", ios::binary | ios::in);
	ifstream fin2("K.txt", ios::binary | ios::in);
	ofstream out("hash.txt", ios::binary | ios::out);
	ofstream out1("gh.txt", ios::binary | ios::out);
	if (!fin1) cout << "error1";
	if (!fin2) cout << "error2";
	if (!out) cout << "error3";
	if (!out1) cout << "error4";
	for (int i =0; i<str.length();++i)
	{


		switch (sw) 
		{
		case 1:
		{
			fin1.read((char *)&a, sizeof(ll));
			fin2.read((char *)&x, sizeof(ll));
			fin2.read((char *)&p, sizeof(ll));
			l = Fpow(a, x, p);
			out.write((char *)&l, sizeof(char));
			out1.write((char *)&str[i], sizeof(char));
			break;
		}
		case 2:
		{
			fin1.read((char *)&r, sizeof(ll));
			fin1.read((char *)&s, sizeof(ll));
			fin2.read((char *)&p, sizeof(ll));
			fin2.read((char *)&y, sizeof(ll));
			fin2.read((char *)&g, sizeof(ll));
			c = (Fpow(y, r, p)*Fpow(r,s,p)) % p;
			out.write((char *)&c, sizeof(char));
			c = Fpow(g, str[i], p);
			out1.write((char *)&c, sizeof(char));
			break;
		}
		case 3:
		{
			fin1.read((char *)&r, sizeof(ll));
			fin1.read((char *)&s, sizeof(ll));
			fin2.read((char *)&p, sizeof(ll));
			fin2.read((char *)&q, sizeof(ll));
			fin2.read((char *)&k, sizeof(ll));
			fin2.read((char *)&a, sizeof(ll));
			fin2.read((char *)&y, sizeof(ll));
			if (!ChkG(str[i], p, q, s, r, a, y))
				f = false;
			break;
		}
		default:
			cout << "Incorrect input" << endl;
		}

	}
	fin1.close();
	fin2.close();
	out.close();
	out1.close();
	if (!f)
		cout << "gost -" << endl;
	else cout << "gost +" << endl;
}
struct Player { int n; ll c = 0; ll d = 0; ll k1; ll k2; };
struct Deck { int n; string card; string lear; bool ex; }D[52];
void Fill(struct Deck K[52])
{
	string lear[4] = { "chervi","bubi","kresti","piki" };
	string card[13] = { "2","3","4","5","6","7","8","9","10","Valet","Dama","Korol'","Tuz"};
	for (int i = 0; i < 52; ++i)
	{
		K[i].n = i + 2;
		K[i].ex = 1;
		K[i].lear = lear[i % 4];
		K[i].card = card[int(i/4)];
			
	}
}
void pD(struct Deck K[52])
{
	for (size_t i = 0; i < 52; i++)
	{
		cout << " n " << K[i].n << " card: " << K[i].card << " lear: " << K[i].lear << " ex " << K[i].ex << endl;
	}
}
void shuffle(struct Deck K[52])
{
	int m, k,n;
	n = rand() % 1000 + 52;
	struct Deck t;
	for (size_t i = 0; i < n ; i++)
	{
		m = rand() % 52;
		k = rand() % 52;
		for (;k == m;)
			m = rand() % 52;
		t = K[m];
		K[m] = K[k];
		K[k] = t;
	}
}

void Poker()
{
	Fill(D);
	pD(D);
	ll p = 0, A[3] = {};
	int n;
	cout << " Input number of players: " << endl;
	cin >> n;
	struct Player *P = new struct Player[n];
	mr(p);
	for (;!simp(p);)
		mr(p);
	for (int i = 0; i < n; ++i)
	{
		P[i].n = i;
		rus(P[i].d);
		Evklid((p - 1), P[i].d, A);
		for (;(P[i].d >= (p - 1) || (A[0] != 1));)
		{
			rus(P[i].d);
			Evklid((p - 1), P[i].d, A);
		}
		P[i].c = A[2];
		if (P[i].c < 0)
			P[i].c += (p - 1);
	}
	ll temp;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < 52; j++)
		{
			temp = Fpow(D[j].n, P[i].c, p);
			D[j].n = temp;
		}
		shuffle(D);
		//pD(D);
		//getchar();
	}
	int r = 0;
	for (size_t i = 0; i < 2*n; i++)
	{
		r = rand() % 52;
		for (;!D[r].ex;)
			r = rand() % 52;
		for (size_t j = 0; j < n; j++)
		{
			
				temp = Fpow(D[r].n, P[(j+i+1)%n].d, p);
				D[r].n = temp;
		}
		if (i < n)
			P[i].k1 = D[r].n;
		else P[i%n].k2 = D[r].n;
		D[r].ex = 0;
		if (i < n)
			cout << " player " << P[i].n << " get card: " << P[i%n].k1 << " " << D[r].card << " " << D[r].lear << endl;
		else cout << " player " << P[i%n].n << " get card: " << P[i%n].k2 << " " << D[r].card << " " << D[r].lear << endl;
		
	}

	bool f = 0;
	cout << " show deck? ";
	cin >> f;
	if(f)
		pD(D);
	
}
struct Bank { int n; ll c; ll d; }B[9];
struct Money { int n; ll m;};

void Emoney() 
{
	
	ll p,q,n,f,r,r1;
	int sum,sb=0;
	int C[9] = {5000,1000,500,100,50,10,5,2,1};
	ll A[3] = {};
	rus(p);
	rus(q);
	for (;!simp(p);)
		rus(p);
	for (;!(simp(q) && (p != q));)
		rus(q);
	n = p*q;
	f = (p- 1)*(q - 1);
	r = rand() % n + 1;
	Evklid(n, r, A);
	for (;A[0] != 1;)
	{

		r = rand() % n + 1;
		Evklid(r, n, A);
	}
	r1 = A[2];
	if (r1 < 0)
		r1 += n;
	A[0] = 0;
	cout << " n = " << n << endl;
	
	
	for (size_t i = 0; i < 9; i++)
	{
		B[i].n = C[i];
		rus(B[i].d);
		Evklid(f, B[i].d, A);
		for (;(B[i].d >= f) || (A[0] != 1);)
		{
			rus(B[i].d);
			Evklid(f, B[i].d, A);
		}
		B[i].c = A[2];
		if (B[i].c < 0)
			B[i].c += f;
		A[0] = 0;
	}
	string th = "", t = "";
	cout << " Input sum: ";
	cin >> sum;
	int tmp = sum;
	for (size_t i = 0; i < 9; ++i)
	{
		for (;(sum / C[i]) >= 1;)
		{
			sum -= C[i];
			++sb;
		}
	}
	struct Money *M = new struct Money[sb];
	unsigned ll **H = new unsigned ll*[sb];
	for (size_t i = 0; i < sb; i++)
	{
		H[i] = new unsigned ll[32];
	}
	for (int i = 0; i < sb; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			H[i][j] = 0;
		}
	}
	unsigned ll **H1 = new unsigned ll*[sb];
	for (size_t i = 0; i < sb; i++)
	{
		H1[i] = new unsigned ll[32];
	}
	unsigned ll **S = new unsigned ll*[sb];
	for (size_t i = 0; i < sb; i++)
	{
		S[i] = new unsigned ll[32];
	}
	
	for (size_t i = 0, j =0; i < sb;)
	{
		if (tmp / C[j] >= 1) 
		{
			M[i].n = C[j];
			tmp -= C[j];
			i++;
		}
		else j++;


	}
	for (int i = 0; i < sb; i++)
	{
		M[i].m = 1 + rand() % (n - 1);
		cout << M[i].m << endl;
		th = Keccak(to_string(M[i].m));
		cout << th << endl;
		for (int j = 0; j < 32; j++)
		{
			t = th.substr(j * 4, 4);
			memcpy(&H[i][j], t.c_str(), 4);
			t = "";
		}
		th = "";
	}
	for (int i = 0; i < sb; i++)
	{
		cout << " Hash of " << i << " banknot:"<<endl;
		cout << "------------------------------" << endl;
		for (int j = 0; j < 32; j++)
		{
			cout << H[i][j] << " ";
		}
		cout << endl;
	}
	int v = 0;
	for (int i = 0; i < sb; i++)
	{
		//cout << " Hash * r^d%n of " << i << " banknot:" << endl;
		//cout << "------------------------------" << endl;
		for (v = 0;M[i].n != B[v].n; v++){}
		for (int j = 0; j < 32; j++)
		{
			H1[i][j] = (H[i][j] % n *Fpow(r, B[v].d, n)) % n;
			//cout << "H^[" << i << "][" << j << "] = " << H[i][j] << "%" << n << "*" << r << "^" << B[v].d << "%" << n << "%" << n << " = " << H1[i][j] << endl;
		}
	}
	for (int i = 0; i < sb; i++)
	{
		//cout << " S^ (H^ ^c) of " << i << " banknot:" << endl;
		//cout << "------------------------------" << endl;
		for (v = 0;M[i].n != B[v].n; v++) {}
		for (int j = 0; j < 32; j++)
		{
			S[i][j] = Fpow(H1[i][j], B[v].c, n);
			//cout << "S^[" << i << "][" << j << "] = " << H1[i][j] <<"^" << B[v].c << "%" << n << " = " << S[i][j] << endl;
		}
	}
	for (int i = 0; i < sb; i++)
	{
		cout <<endl<< " S (S^ * r1) of " << i << " banknot:" << endl;
		cout << "------------------------------" << endl;
		for (int j = 0; j < 32; j++)
		{
			H1[i][j] = (S[i][j]*r1)%n;
			//cout << "S[" << i << "][" << j << "] = " << S[i][j] << "*" << r1 << "%" << n << " = " << H1[i][j] << endl;
			cout << H1[i][j] << " ";
		}
	}
	for (int i = 0; i < sb; i++)
	{
		cout <<endl<< " H ^ c of " << i << " banknot:" << endl;
		cout << "------------------------------" << endl;
		for (v = 0;M[i].n != B[v].n; v++) {}
		for (int j = 0; j < 32; j++)
		{
			S[i][j] = Fpow(H[i][j], B[v].c, n);
			//cout << "H ^ c[" << i << "][" << j << "] = " << H[i][j] << "^" << B[v].c << "%" << n << " = " << S[i][j] << endl;
			cout << S[i][j] << " ";
		}
	}
	for (int i = 0; i < sb; i++)
	{
		cout <<endl<< " chek " << i << " (" << M[i].n << "):" << endl;
		for (int j = 0; j < 32; j++)
		{
			if (S[i][j] == H1[i][j])
				cout << "true ";
			else
			{
				cout << "false ";
				break;
			}
		}
	}
	delete[] M;
	delete[] H;
	delete[] H1;
	delete[] S; 
	
} 
struct reb { ll x; ll y; }r;

void fqwe(vector<reb> z, vector<ll> r, ll m, ll n, ll key, ll os)
{
	ll t = 0;
	cout << " Enc gr (only gc): " << endl;
	for each (reb i in z)
	{
		cout << endl << i.x << "-" << i.y << endl;
	}
	for (int i = 0; i < n; i++)
	{
		t = Fpow(r[i], key, os);
		r[i] = t;
	}
	cout << endl << " gc: " << endl;
	for each (ll i in r)
	{
		cout <<i<<"-";
	}
	cout << endl;
}

void sqwe(vector<reb> z, vector<ll> r, ll m, ll n, ll key, ll os)
{
	ll t = 0;
	cout << endl << " Second qwestion: " << endl;
	for (int i = 0; i < m; i++)
	{
		t = Fpow(z[i].x, key, os);
		z[i].x = t;
		t = Fpow(z[i].y, key, os);
		z[i].y = t;
	}
	cout << " Graph:" << endl;
	for each (reb i in z)
	{
		cout << endl << i.x << "-" << i.y << endl;
	}
	for (int i = 0; i < n; i++)
	{
		t = Fpow(r[i], key, os);
		r[i] = t;
	}
	cout << " History of changes:" << endl;
	for each (ll i in r)
	{
		cout <<i<< endl;
	}

	
}

void Gamilton()
{
	ll m = 0, n = 0,t = 0, c, d, p;
	char io=0;
	vector<reb> a,b,res;
	vector<ll> g,h,rl;
	ifstream in("gc.txt", ios::binary | ios::in);
	in >> m;
	in >> n;
	for (int i = 0; i < m; ++i)
	{
		in >> r.x;
		in >> r.y;
		a.push_back(r);
		res.push_back(r);
	}
	for (int i = 0; i < n; ++i)
	{
		rl.push_back(i + 2);
	}
	for (int i = 0; i < n; ++i)
	{
		in >> t;
		g.push_back(t);
	}
	in.close();
	for each (ll i in g)
	{
		cout <<i<<"-";
	}
	for each (reb i in a)
	{
		cout <<endl<< i.x << "-" << i.y << endl;
	}
	RSA(io,c, d, p);
	cout << " c = " << c << "d = " << d << " p = " << p << endl;
	cout << Fpow(Fpow(55, c, p), d, p) << endl;
	for (int i = 0; i < m; i++)
	{
		t = rand() % (m - i);
		b.push_back(a[t]);
		a.erase(a.begin()+t);
	}
	for (int i = 0; i < n; i++)
	{
		t = rand() % (n - i);
		h.push_back(rl[t]);
		rl.erase(rl.begin() + t);
	}
	for each (reb i in b)
	{
		cout << endl << i.x << "-" << i.y << endl;
	}
	for (int i = 0; i < n; i++)
	{
		t = Fpow(h[i], c, p);
		h[i] = t;
	}
	for each (ll i in h)
	{
		cout << endl << i<< endl;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (b[j].x == (i + 2))
				b[j].x = h[i];
			else if (b[j].y == (i + 2))
				b[j].y = h[i];
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (g[j] == (i + 2))
				g[j] = h[i];
		}
	}
	
	/*cout << " Enc gr: " << endl;
	for each (reb i in b)
	{
		cout << endl << i.x << "-" << i.y << endl;
	}*/
	cout << " Enc gc: " << endl;
	for each (ll i in g)
	{
		cout << endl << i << endl;
	}
	
	//sqwe(b, h, m, n, d, p);
	vector<ll> gamr(g);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (b[j].x == gamr[i%n] && b[j].y == gamr[(i+1)%n] || b[j].x == gamr[(i+1)%n] && b[j].y == gamr[i%n])
			{
				t = Fpow(b[j].x,d,p);
				b[j].x = t;
				t = Fpow(b[j].y, d, p);
				b[j].y = t;
			}
		}
	}
	fqwe(b, g, m, n, d, p);
	

}
