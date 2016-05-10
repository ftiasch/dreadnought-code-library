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

void ExtendedKMP(char *s, int next[]) {
    int l = strlen(s), i = 0, j = 0, k = 1;
    while (1 + j < l && s[j] == s[1 + j]) {
        ++j;
    }
    next[1] = j;
    for (int i = 2; i < l; ++i) {
        int len = k + next[k], ll = next[i - k];
        if (ll < len - i) {
            next[i] = ll;
        } else {
            j = max(0, len - i);
            while (i + j < l && s[j] == s[i + j]) {
                ++j;
            }
            next[i] = j;
            k = i;
        }
    }
}
