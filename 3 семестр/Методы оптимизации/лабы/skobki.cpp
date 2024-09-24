#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

typedef struct skobka{
	int f1_1 = 0;
	int f1_2 = 0;
	int f2_1 = 0;
	int f2_2 = 0;
} SKOBKA;

const string name_file = "input_2.txt";

void read_f(vector<int> &v)
{
	v.clear();
	ifstream in(name_file);

	int N = 0, buf = 0;;
	in >> N;

	for(int i = 0; i < N ; i++)
	{
		in >> buf;
		v.push_back(buf);
	}
	in.close();
}

void print_matr(vector<vector<int> > f)
{
	size_t N = f.size();

	for(int i = 1 ; i < N; i++)
	{
		for(int j = 0; j < i; j++) cout << " " <<setw(10);
		for(int j = i ; j < N; j++)
		{
			cout << f[i][j];
			if(j < N-1) cout << setw(10);
		}
		cout << endl;
	}
}

void answ(vector<pair<int,int> > &answer,pair<int,int> pair_sk,vector<vector<SKOBKA> > all_skobki)
{
	if(pair_sk.second == pair_sk.first)
	{
		return;
	}
	else
	{
		if(!(pair_sk.first == 1 && pair_sk.second == answer.size()))
		{
			answer[pair_sk.first-1].first++;
			answer[pair_sk.second-1].second++;
		}

		int s1 = all_skobki[pair_sk.first][pair_sk.second].f1_1;
		int s2 = all_skobki[pair_sk.first][pair_sk.second].f1_2;
		int s3 = all_skobki[pair_sk.first][pair_sk.second].f2_1;
		int s4 = all_skobki[pair_sk.first][pair_sk.second].f2_2;
		answ(answer,pair<int,int>(s1,s2),all_skobki);
		answ(answer,pair<int,int>(s3,s4),all_skobki);
	}
}

int main()
{
	vector<int> r;

	read_f(r);
	size_t N = r.size() - 1;

	for(int i = 0; i < r.size(); i++)
	{
		cout << "r[" << i << "] = " << r[i] << endl;
	}
	cout << endl;

	vector<vector<int> > f(N+1,vector<int>(N+1,0));
	vector<vector<SKOBKA> > all_skobki(N+1,vector<SKOBKA>(N+1));

	cout << "Matrix: " << endl;
	for(int i = 1; i < r.size(); i++)
	{
		cout << "M" << i << "[ " << r[i-1] <<" x "<< r[i] << " ]" << endl;
	}
	cout << "Matrix numbers: " << r.size() - 1 << endl << endl;

	vector<pair<int,int> > answer(r.size() - 1);

	int N_k = N, k, t;
	for (t = 1; t < N; t++)
	{
		for (k = 1; k < N_k ; k++){

			int min = 2000000000, s1 = 0 ,s2 = 0 ,s3 = 0 ,s4 = 0;
			cout << "f(" << k << "," << k+t << ") = min(";
			for (int j = k; j <= k+t-1; j++){
				cout << "f(" << k << "," <<j<<") + f(" << j+1 << "," << k+t << ") + "<< r[k-1] << "*" << r[j] << "*" <<r[k+t];

				int sum = f[k][j] + f[j+1][k+t] + r[k-1]*r[j]*r[k+t];
				if(j < k+t-1) cout << ", ";
				if(sum < min)
				{
					min = sum;
					s1	= k;
					s2	= j;
					s3	= j + 1;
					s4	= k + t;
				}
			}
			cout << ") = " << min << endl;
			f[k][k+t] = min;
			all_skobki[k][k+t].f1_1 = s1;
			all_skobki[k][k+t].f1_2 = s2;
			all_skobki[k][k+t].f2_1 = s3;
			all_skobki[k][k+t].f2_2 = s4;
		}
		N_k--;
	}
	cout << endl << "Matrix T:" << endl;
	print_matr(f);

	cout << endl;

	answ(answer,pair<int,int>(k-1,(k-1) + (t-1)),all_skobki);
	cout << endl << "__________________________________________________________" << endl << "Result:\t";

	for(int i = 0; i < answer.size(); i++)
	{
		for(int j = 0; j < answer[i].first; j++) cout << " ( ";
		cout << "M" << i+1 << " ";
		for(int j = 0; j < answer[i].second; j++) cout << ") ";
	}
	cout << endl << "The complexity of multiplication:\t" << f[k-1][(k-1) + (t-1)]<<endl;
}