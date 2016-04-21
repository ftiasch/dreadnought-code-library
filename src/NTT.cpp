const int N = , P = 786433, G = 10;
void dft(int *x, int on, int n) {
	int k, id, r, tmp, u, t;
	for(int i = 1, j = n >> 1; i < n - 1; ++ i) {
		if (i < j) swap(x[i], x[j]);
		for(k = n >> 1; j >= k; j -= k, k >>= 1);
		j += k;
	}
	for(int h = 2; h <= n; h <<= 1) {
		r = modPow(G, (P - 1) / h, P);
		if (on < 0) r = modPow(r, P - 2, P);
		for(int j = 0, p = h >> 1; j < n; j += h) {
			for(int k = j, w = 1; k < j + p; k ++) {
				u = x[k]; id = k + p;
				t = (long long)w * x[id] % P;
				x[k] = (u + t) % P;
				x[id] = (u - t + P) % P;
				w = (long long)w * r % P;
}}}}
int xa[N], xb[N];
void dft(int *a, int lenA, int *b, int lenB, int *ans, int &lenAns) {
	for(lenAns = 1; lenAns < lenA + lenB; lenAns <<= 1);
	for(int i = 0; i < lenAns; ++ i) xa[i] = xb[i] = 0;
	for(int i = 0; i < lenA; ++ i) xa[i] = a[i] % P;
	for(int i = 0; i < lenB; ++ i) xb[i] = b[i] % P;
	dft(xa, 1, lenAns); dft(xb, 1, lenAns);
	for(int i = 0; i < lenAns; ++ i) xa[i] = (long long)xa[i] * xb[i] % P;
	dft(xa, -1, lenAns);
	int tmp = modPow(lenAns, P - 2, P);
	for(int i = 0; i < lenAns; ++ i) ans[i] = (long long)xa[i]* tmp % P;
}
