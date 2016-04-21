// Area[i] 表示覆盖次数大于等于 i 的面积
struct Tevent {
	Point p; double ang; int add;
	Tevent() {}
	Tevent(const Point &_p, double _ang, int _add): p(_p), ang(_ang), add(_add) {}
	bool operator <(const Tevent &a) const {
		return ang < a.ang;
	}
} eve[N * 2];
int E, cnt, C;
Circle c[N];
bool g[N][N], overlap[N][N];
double Area[N];
int cX[N], cY[N], cR[N];
bool contain(int i, int j) {
	return (sign(c[i].r - c[j].r) > 0|| sign(c[i].r - c[j].r) == 0 && i < j) && c[i].contain(c[j], -1);
}
int main() {
	scanf("%d", &C);
	for (int i = 0; i < C; ++i) {
		scanf("%d%d%d", cX+i, cY+i, cR+i);
		c[i].o = Point(cX[i], cY[i]);
		c[i].r = cR[i];
	}
	for (int i = 0; i <= C; ++i) Area[i] = 0;
	for (int i = 0; i < C; ++i) for (int j = 0; j < C; ++j)
			overlap[i][j] = contain(i, j);
	for (int i = 0; i < C; ++i) for (int j = 0; j < C; ++j) 
		g[i][j] = !(overlap[i][j] || overlap[j][i] || c[i].disjuct(c[j], -1));
	for (int i = 0; i < C; ++i) {
		E = 0; cnt = 1;
		for (int j = 0; j < C; ++j) if (j != i && overlap[j][i]) cnt++;
		for (int j = 0; j < C; ++j) {
			if (i != j && g[i][j]) {
				Point aa, bb;
				isCC(c[i], c[j], aa, bb);
				double A = atan2(aa.y - c[i].o.y, aa.x - c[i].o.x);
				double B = atan2(bb.y - c[i].o.y, bb.x - c[i].o.x);
				eve[E++] = Tevent(bb, B, 1);
				eve[E++] = Tevent(aa, A, -1);
				if (B > A) cnt++;
			}
		}
		if (E == 0) { //cnt 表示覆盖次数超过 cnt
			Area[cnt] += PI * c[i].r * c[i].r;
		} else {
			sort(eve, eve + E);
			eve[E] = eve[0];
			for (int j = 0; j < E; ++j) {
				cnt += eve[j].add; 
				Area[cnt] += eve[j].p.det(eve[j + 1].p) * .5;
				double theta = eve[j + 1].ang - eve[j].ang;
				if (theta < 0) theta += PI * 2.;
				Area[cnt] += theta * c[i].r * c[i].r * .5 - sin(theta) * c[i].r * c[i].r * .5;
			}
		}
	}
	for(int i = 1; i <= C; ++ i) printf("[%d] = %.3f\n", i, Area[i] - Area[i + 1]);
}
