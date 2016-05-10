void Manacher(char text[], int n, int palindrome[]) {
	palindrome[0] = 1;
	for (int i = 1, j = 0, i < (n << 1) - 1; ++ i) {
		int p = i >> 1;
		int q = i - p;
		int r = (j + 1 >> 1) + palindrome[j] - 1;
		palindrome[i] = r < q ? 0 : min(r - q + 1, palindrome[(j << 1) - i]);
		while (0 <= p - palindrome[i] && q + palindrome[i] < n && text[p - palindrome[i]] == text[q + palindrome[i]]) {
			palindrome[i] ++;
		}
		if (q + palindrome[i] - 1 > r) {
			j = i;
		}
	}
}
void ExtendedKMP(char *a, char *b, int M, int N, int *Next, int *ret) {// a -> 模式串 b -> 匹配串
	int i, j, k;
	for (j = 0; 1 + j < M && a[j] == a[1 + j]; j++); Next[1] = j;
	k = 1;
	for (i = 2; i < M; i++) {
		int Len = k + Next[k], L = Next[i - k];
		if (L < Len - i) {
			Next[i] = L;
		} else {
			for (j = max(0, Len - i); i + j < M && a[j] == a[i + j]; j++);
			Next[i] = j;
			k = i;
		}
	}
	for (j = 0; j < N && j < M && a[j] == b[j]; j++);
	ret[0] = j;
	k = 0;
	for (i = 1; i < N; i++) {
		int Len = k + ret[k], L = Next[i - k];
		if (L < Len - i) {
			ret[i] = L;
		} else {
			for (j = max(0, Len - i); j < M && i + j < N && a[j] == b[i + j]; j++);
			ret[i] = j;
			k = i;
		}
	}
}

