const int MAX_N = 1000000 + 10;
int rank[MAX_N], height[MAX_N];
int cmp(int *x, int a, int b, int d) {
	return x[a] == x[b] && x[a + d] == x[b + d];
}

void doubling(int *a, int N, int M) {
	static int sRank[MAX_N], tmpA[MAX_N], tmpB[MAX_N];
	int *x = tmpA, *y = tmpB;
	for(int i = 0; i < M; ++ i) sRank[i] = 0;
	for(int i = 0; i < N; ++ i) ++ sRank[x[i] = a[i]];
	for(int i = 1; i < M; ++ i) sRank[i] += sRank[i - 1];
	for(int i = N - 1; i >= 0; -- i) sa[-- sRank[x[i]]] = i;
	
	for(int d = 1, p = 0; p < N; M = p, d <<= 1) {
		p = 0; for(int i = N - d; i < N; ++ i) y[p ++] = i;
		for(int i = 0; i < N; ++ i)
			if (sa[i] >= d) y[p ++] = sa[i] - d;
		for(int i = 0; i < M; ++ i) sRank[i] = 0;
		for(int i = 0; i < N; ++ i) ++ sRank[x[i]];
		for(int i = 1; i < M; ++ i) sRank[i] += sRank[i - 1];
		for(int i = N - 1; i >= 0; -- i) sa[-- sRank[x[y[i]]]] = y[i];
		swap(x, y); x[sa[0]] = 0; p = 1;
		for(int i = 1; i < N; ++ i)
			x[sa[i]] = cmp(y, sa[i], sa[i - 1], d) ? p - 1 : p ++;
	}
}

void calcHeight() {
	for(int i = 0; i < N; ++ i) rank[sa[i]] = i;
	int cur = 0;
	for(int i = 0; i < N; ++ i)
	if (rank[i]) {
		if (cur) cur --;
		for( ; a[i + cur] == a[sa[rank[i] - 1] + cur]; ++ cur);
		height[rank[i]] = cur;
	}
}