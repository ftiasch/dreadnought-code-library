#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;

typedef unsigned long long ull;

ull sqrtll(ull n)
{
	if (n == 0) return 0;
	ull x = 1ull << ((63 - __builtin_clzll(n)) >> 1);
	ull xx = -1;
	for( ; ; ) {
		ull nx = (x + n / x) >> 1;
		if (nx == xx)
			return min(x, nx);
		xx = x;
		x = nx;
	}
}

int main()
{
	srand(time(0));
	ull a, b, x;
	a = rand();
	b = rand();
	int flag = true;
	for( ; ; ) {
		x = x * a + b;
		ull r1 = sqrtll(x);
		ull r2 = (ull)(sqrt(x) + 0.5);
		if (r1 != r2) {
			flag = false;	
			cout << x << ' ' << r1 << ' ' << r1 * r1 << ' ' << r2 << ' ' << r2 * r2 << endl;
			break;
		}
	}
	if (flag) cout << "!!" << endl;
	return 0;
}
