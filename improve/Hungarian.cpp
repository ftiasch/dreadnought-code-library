// 最小匹配, 自带初始化 n <= m 方案存在 p[] 中
const int N = 105;
const int INF = 1000000000; // 严格大于最大边权
int n, m, a[N][N];
int u[N], v[N], p[N], fa[N], minv[N];
bool used[N];
int km() {
	memset(u, 0, sizeof(int) * n);
	for (int i = 0; i <= m; ++i) v[i] = 0, p[i] = n;
	for (int i = 0; i < n; ++i) {
		p[m] = i;
		int j0 = m;
		for (int j = 0; j <= m; ++j) minv[j] = INF, used[j] = false;
		do {
			used[j0] = true;
			int i0 = p[j0], delta = INF, j1;
			for (int j = 0; j < m; ++j) {
				if (!used[j]) {
					int cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, fa[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
			}
			for (int j = 0; j <= m; ++j) {
				if (used[j]) {
					u[p[j]] += delta, v[j] -= delta;
				} else {
					minv[j] -= delta;
				}
			}
			j0 = j1;
		} while (p[j0] != n);
		do {
			int j1 = fa[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0 != m);
	}
	return -v[m];
}
