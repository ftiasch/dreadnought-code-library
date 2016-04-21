#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 201;
const int MOD = 1000000000 + 7;

long long n;
int wa, wb, m;
int a[N], b[N];
long long c[N], f[N], d[N];

int linearRecurrence(long long n, int m, long long a[], long long c[], int p) {
	long long v[N] = {1 % p}, u[N << 1], msk = !!n;
	for(long long i = n; i > 1; i >>= 1) msk <<= 1;
	for(long long x = 0; msk; msk >>= 1, x <<= 1) {
		fill_n(u, m << 1, 0);
		int b = !!(n & msk); x |= b;
		if(x < m) u[x] = 1 % p;
		else {
			for(int i = 0; i < m; ++i)
				for(int j = 0, t = i + b; j < m; ++j, ++t)
					u[t] = (u[t] + v[i] * v[j]) % p;
			for(int i = (m << 1) - 1; i >= m; --i)
				for(int j = 0, t = i - m; j < m; ++j, ++t)
					u[t] = (u[t] + c[j] * u[i]) % p;
		}
		copy(u, u + m, v);
	}
	int an = 0;
	for(int i = 0; i < m; ++i) an = (an + v[i] * a[i]) % p;
	return an;
}

void solve()
{
	cin >> wa;
	for(int i = 0; i < n; ++ i) {
		cin >> a[i];
	}
	cin >> wb;
	m = 0;
	for(int i = 0; i < n; ++ i) {
		cin >> b[i];
		m = max(m, b[i]);
	}
	c[0] = 1;
	for(int i = 1; i <= m; ++ i) {
		c[i] = 0;
		for(int j = 0; j < wa; ++ j) {
			if (i >= a[j]) {
				c[i] = (c[i - a[j]] + c[i]) % MOD;
			}
		}
		cout << "!!" << i << ' ' << c[i] << endl;
	}

	for(int i = 0; i < m; ++ i) d[i] = 0;
	for(int i = 0; i < wa; ++ i)
		if (a[i] <= m) {
			d[m - a[i]] = c[a[i]];
		}
	f[0] = 1;
	for(int i = 1; i < m; ++ i) {
		f[i] = 0;
		for(int j = 0; j < wa; ++ j) {
			if (i >= a[j]) f[i] = (f[i] + f[i - a[j]] * c[a[j]]) % MOD;
		}
	}
	for(int i = 0; i < m; ++ i) {
		cout << i << ' ' << f[i] << endl;
	}
}

int main()
{
	for( ; cin >> n; )
		solve();
	return 0;
}
