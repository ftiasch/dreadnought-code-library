#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#include<vector>
#include<string>
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

#define MP make_pair
#define PB push_back
#define foreach(e,x) for(__typedef(x.begin()) e=x.begin(); e!=x.end(); ++e)

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> mapII;

const double INF = 1e7;
const int N = 100000 + 10;
const double EPS = 1e-8;

struct Point
{
	double x, y;
	Point() {
	}
	Point(double _x, double _y) {
		x = _x; y = _y;
	}
	Point operator + (const Point &that) const {
		return Point(x + that.x, y + that.y);
	}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	Point operator * (const double &that) const {
		return Point(x * that, y * that);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	Point unit() {
		double d = abs();
		return Point(x / d, y / d);
	}
	Point rot90() {
		return Point(y, -x);
	}
};

struct Circle
{
	double r;
	Point c;
};

int n;
double sx, sy, d;
Point p[N];
Circle cir[N];

int sign(double c)
{
	return c < - EPS ? -1 : c > EPS;
}

void getRange(double x, Circle &cir, double &retl, double &retr)
{
	double tmp = cir.r * cir.r - (cir.c.x - x) * (cir.c.x - x);
	tmp = max(tmp, 0.0);
	tmp = sqrt(tmp);
	retl = cir.c.y - tmp;
	retr = cir.c.y + tmp;
}

int checkInLine(double x)
{
	double minR = INF, maxL = - INF;
	double tmpl, tmpr;
	for(int i = 0; i < n; ++ i) {
		if (cir[i].c.x + cir[i].r < x || cir[i].c.x - cir[i].r > x) return false;
		getRange(x, cir[i], tmpl, tmpr);
		maxL = max(tmpl, maxL);
		minR = min(tmpr, minR);
		if (maxL > minR) return false;
	}
	return true;
}

double disPtoP(const Point &a, const Point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int interCtoC(Circle &c1, Circle &c2)
{
	return sign(disPtoP(c1.c, c2.c) - (c1.r + c2.r)) <= 0;
}

Point getInterCtoC(Circle &c1, Circle &c2)
{
	double d = disPtoP(c1.c, c2.c);
	double d1 = (d * d - c2.r * c2.r + c1.r * c1.r) / (2 * d);
	Point vec = (c2.c - c1.c).unit();
	Point inter = c1.c + vec * d1;
	vec = vec.rot90();
	double d2 = c1.r * c1.r - disPtoP(inter, c1.c) * disPtoP(inter, c1.c);
	d2 = max(d2, 0.0);
	vec = vec.unit() * sqrt(d2);
	return vec + inter;
}

int shouldGoLeft(double x)
{
	if (checkInLine(x)) return 2;
	int onL = 0, onR = 0;
	for(int i = 0; i < n; ++ i) {
		if (cir[i].c.x + cir[i].r < x) onL = 1;
		if (cir[i].c.x - cir[i].r > x) onR = 1;
	}
	if (onL && onR) return -1;
	if (onL) return 1;
	if (onR) return 0;

	double range0r = INF; 
	double range1l = -INF;
	double tmpl, tmpr;
	int id0, id1;

	for(int i = 0; i < n; ++ i) {
		getRange(x, cir[i], tmpl, tmpr);
		if (tmpr < range0r) {
			range0r = tmpr;
			id0 = i;
		}
		if (tmpl > range1l) {
			range1l = tmpl;
			id1 = i;
		}
	}

	if (! interCtoC(cir[id0], cir[id1])) return -1;
	Point inter = getInterCtoC(cir[id0], cir[id1]);
	if (inter.x < x) return 1;
	return 0;
}

int checkInter()
{
	double l = -INF, r = INF, mid;
	for(int i = 0; i < 100; ++ i) {
		mid = (l + r) * 0.5;
		int tmp = shouldGoLeft(mid);
		if (tmp < 0) return 0;
		if (tmp == 2) return 1;
		if (tmp) {
			r = mid;
		} else {
			l = mid;
		}
	}

	mid = (l + r) * 0.5;
	return checkInLine(mid);
}

int checkDis(double r)
{
	cir[n - 1].c = Point(sx, sy);
	cir[n - 1].r = r;
	return checkInter();
}

void solve()
{
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}

	for(int i = 0; i < n; ++ i) {
		cir[i].c = p[i];
		cir[i].r = d;
	}

	if (! checkInter()) {
		puts("X");
		return;
	}

	++ n;

	double l = 0, r = INF, mid;
	for(int i = 0; i < 100; ++ i) {
		mid = (l + r) * 0.5;
		if (checkDis(mid)) r = mid;
		else l = mid;
	}

	printf("%.2f\n", r);
}

int main()
{
	for( ; cin >> sx >> sy >> d; ) {
		solve();
	}
	return 0;
}


