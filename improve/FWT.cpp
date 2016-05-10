void FWT(int a[N], int N) {
	for (int d = 1; d < N; d <<= 1) {
		int d2 = d << 1;
		for (int i = 0; i < N; i += d2) {
			int *x = a + i, *y = a + i + d;
			for (int j = 0; j < d; ++j, ++x, ++y) {
				if ((*x += *y) >= MOD) {
					*x -= MOD;
				}
				if ((*y = *x - (*y << 1)) < 0) {
					if ((*y += MOD) < 0) {
						*y += MOD;
					}
				}
			}
		}
	}
}

void xorPow(int a[N], int n, int b[N]) {
	memset(b, 0, sizeof(int) * N);
	b[0] = 1;
	FWT(a, N);
	FWT(b, N);
	while(n) {
		if (n & 1) {
			dot(b, a, N);
		}
		dot(a, a, N);
		n >>= 1;
	}
	FWT(b, N);
	norm(b, N);
}
