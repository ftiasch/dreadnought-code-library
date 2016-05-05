//R 是 2^n*q+1 形质数 p 的原根
void NFT(int P[], int n, int oper) {
	for (int i = 1, j = 0; i < n - 1; ++i) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) {
			swap(P[i], P[j]);
		}
	}
	for (int d = 0; (1 << d) < n; ++d) {
		int m = 1 << d, m2 = m * 2;
		int unit_p0 = powmod(R, (MOD - 1) / m2);
		if (oper < 0) {
			unit_p0 = inverse(unit_p0); 
		}
		for (int i = 0; i < n; i += m2) {
			int unit = 1;
			for (int j = 0; j < m; ++j) {
				int &P1 = P[i + j + m], 
					&P2 = P[i + j];
				int t = (long long)unit * P1 % MOD;
				P1 = (P2 - t + MOD) % MOD;
				P2 = (P2 + t) % MOD;
				unit = (long long)unit * unit_p0 % MOD;
			}
		}
	}
}
