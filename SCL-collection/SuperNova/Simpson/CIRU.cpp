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

const int N = 1000 + 10;
const double EPS = 1e-8;

struct Circle
{
	double x, y, r;
} a[N];

int n;

void solve()
{
	for(int i = 0; i < n; ++ i) {
		scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].r);
	}
}

int main()
{
	for( ; cin >> n; ) {
		solve();
	}
	return 0;
}

