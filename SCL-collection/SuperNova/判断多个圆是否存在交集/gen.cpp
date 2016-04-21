#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

using namespace std;

#define MP make_pair
#define PB push_back
#define foreach(e,x) for(__typedef(x.begin()) e=x.begin(); e!=x.end(); ++e)

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> mapII;

const int N = 100000 + 10;
const double EPS = 1e-8;

int sx, sy, d;

void solve()
{
	sx = rand() % 100; sy = rand() % 100;
	d = rand() % 100;
	int n = rand() % 10 + 1;
	cout << sx << ' ' << sy << ' ' << d << endl;
	cout << n << endl;
	for(int i = 0; i < n; ++ i) {
		int x = rand() % 100, y = rand() % 100;
		cout << x << ' ' << y << endl;
	}
}

int main()
{
	srand(time(0));
	int test = 10;
	for(int i = 0; i < test; ++ i)
		solve();
	return 0;
}

