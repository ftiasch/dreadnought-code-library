struct Tcir {
	point o;
	double r;
	Tcir() {
	}
	Tcir(const point &o, double r): o(o), r(r) {
	}
};
struct Tevent {
	point p;
	double ang;
	int add;
	Tevent() {
	}
	Tevent(const point &_p, double _ang, int _add): p(_p), ang(_ang), add(_add) {
	}
	bool operator <(const Tevent &a) const {
		return ang < a.ang;
	}
} eve[maxn * 2];
int E, cnt;
double sqr(double x) { return x * x; }
void circleCrossCircle(const Tcir &a, const Tcir &b) {
	double l = (a.o - b.o).len2();
	double s = ((a.r - b.r) * (a.r + b.r) / l + 1) * .5;
	double t = sqrt(-(l - sqr(a.r - b.r)) * (l - sqr(a.r + b.r)) / (l * l * 4.));
	point dir = b.o - a.o;
	point Ndir = point(-dir.y, dir.x);
	point aa = a.o + dir * s + Ndir * t;
	point bb = a.o + dir * s - Ndir * t;
	double A = atan2(aa.y - a.o.y, aa.x - a.o.x);
	double B = atan2(bb.y - a.o.y, bb.x - a.o.x);
	eve[E++] = Tevent(bb, B, 1);
	eve[E++] = Tevent(aa, A, -1);
	if (B > A) {
		cnt++;
	}
}
bool contain(int x1, int y1, int r1, int x2, int y2, int r2) {
	return r1 >= r2 && (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 - r2) * (r1 - r2);
}
bool disjoint(int x1, int y1, int r1, int x2, int y2, int r2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) >= (r1 + r2) * (r1 + r2);
}
bool Same(int x1, int y1, int r1, int x2, int y2, int r2) {
	return r1 == r2 && x1 == x2 && y1 == y2;
}
bool g[maxn][maxn], Overlap[maxn][maxn];
double Area[maxn];
int cX[maxn], cY[maxn], cR[maxn];
Tcir c[maxn];
int C;
int main() {
	scanf("%d", &C);
	for (int i = 0; i < C; ++i) {//去掉重复的圆
		scanf("%d%d%d", cX+i, cY+i, cR+i);

		bool found = false;
		for (int j = 0; j < i; ++j) {
			if (Same(cX[i], cY[i], cR[i], cX[j], cY[j], cR[j])) {
				found = true;
				break;
			}
		}
		if (found) {
			i--;
			C--;
			continue;
		}
		c[i] = Tcir(point(cX[i], cY[i]), cR[i]);
	}

	for (int i = 0; i <= C; ++i) Area[i] = 0;
	for (int i = 0; i < C; ++i) {
		for (int j = 0; j < C; ++j) {
			Overlap[i][j] = contain(cX[i], cY[i], cR[i], cX[j], cY[j], cR[j]);
		}
	}
	for (int i = 0; i < C; ++i) {
		for (int j = 0; j < C; ++j) {
			g[i][j] = !(Overlap[i][j] || Overlap[j][i] || disjoint(cX[i], cY[i], cR[i], cX[j], cY[j], cR[j]));
		}
	}
	for (int i = 0; i < C; ++i) {
		E = 0;
		cnt = 1;
		for (int j = 0; j < C; ++j) if (j != i && Overlap[j][i]) cnt++;
		for (int j = 0; j < C; ++j) {
			if (i != j && g[i][j]) {
				circleCrossCircle(c[i], c[j]);
			}
		}
		//cnt表示覆盖次数超过cnt
		if (E == 0) {
			Area[cnt] += PI * c[i].r * c[i].r;
		} else {
			double counts = 0;
			sort(eve, eve + E);
			eve[E] = eve[0];
			for (int j = 0; j < E; ++j) {
				cnt += eve[j].add; 
				Area[cnt] += cross(eve[j].p, eve[j + 1].p) * .5;
				double theta = eve[j + 1].ang - eve[j].ang;
				if (theta < 0) theta += PI * 2.;
				Area[cnt] += theta * c[i].r * c[i].r * .5 - sin(theta) * c[i].r * c[i].r * .5;
			}
		}
	}
	printf("%.5f\n", Area[1]);
	return 0;
}

