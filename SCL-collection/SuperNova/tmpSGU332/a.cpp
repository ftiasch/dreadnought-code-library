#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <cmath>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

struct Point {
	double x, y;
	Point() {
	}
	Point(double _x, double _y) :
			x(_x), y(_y) {
	}
	Point operator+(const Point&p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point&p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(double d) const {
		return Point(x * d, y * d);
	}
	Point operator/(double d) const {
		return Point(x / d, y / d);
	}
	double det(const Point&p) const {
		return x * p.y - y * p.x;
	}
	double dot(const Point&p) const {
		return x * p.x + y * p.y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	Point rot90() const {
		return Point(-y, x);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	void write() const {
		printf("%lf %lf\n", x, y);
	}
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))

const double EPS = 1e-12;
inline int sign(double a) {
	return a < -EPS ? -1 : a > EPS;
}

#define crossOp(p1,p2,p3) (sign(cross(p1,p2,p3)))

Point isSS(Point p1, Point p2, Point q1, Point q2) {
	double a1 = cross(q1,q2,p1), a2 = -cross(q1,q2,p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

struct Border {
	Point p1, p2;
	double alpha;
	void setAlpha() {
		alpha = atan2(p2.y - p1.y, p2.x - p1.x);
	}
	void read() {
		p1.read();
		p2.read();
		setAlpha();
	}
};

int n;
const int MAX_N_BORDER = 20000 + 10;
Border border[MAX_N_BORDER], nboarder[MAX_N_BORDER];

bool operator<(const Border&a, const Border&b) {
	int c = sign(a.alpha - b.alpha);
	if (c != 0)
		return c == 1;
	return crossOp(b.p1,b.p2,a.p1) >= 0;
}

bool operator==(const Border&a, const Border&b) {
	return sign(a.alpha - b.alpha) == 0;
}

const double LARGE = 10000;

void add(double x, double y, double nx, double ny) {
	border[n].p1 = Point(x, y);
	border[n].p2 = Point(nx, ny);
	border[n].setAlpha();
	n++;
}

Point isBorder(const Border&a, const Border&b) {
	return isSS(a.p1, a.p2, b.p1, b.p2);
}

Border que[MAX_N_BORDER];
int qh, qt;

bool check(const Border&a, const Border&b, const Border&me) {
	Point is = isBorder(a, b);
	return crossOp(me.p1,me.p2,is) > 0;
}

void convexIntersection(Border *border) {
	qh = qt = 0;
	sort(border, border + n);
	n = unique(border, border + n) - border;
	for (int i = 0; i < n; ++i) {
		Border cur = border[i];
		while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], cur))
			--qt;
		while (qh + 1 < qt && !check(que[qh], que[qh + 1], cur))
			++qh;
		que[qt++] = cur;
	}
	while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], que[qh]))
		--qt;
	while (qh + 1 < qt && !check(que[qh], que[qh + 1], que[qt - 1]))
		++qh;
}

bool calcArea() {
	static Point ps[MAX_N_BORDER];
	int cnt = 0;

	/*
	for(int i = qh; i < qt; ++ i) {
		cout << "new board " << endl;
		que[i].p2.write();
		que[i].p1.write();
	}
	*/
	if (qt - qh <= 2) {
		return false;
	}

	for (int i = qh; i < qt; ++i) {
		int next = i + 1 == qt ? qh : i + 1;
		ps[cnt++] = isBorder(que[i], que[next]);
	}

	long double area = 0;
	for (int i = 0; i < cnt; ++i) {
		area += ps[i].det(ps[(i + 1) % cnt]);
	}
	area /= 2;
	return abs(area) > EPS;
}

Point tp[MAX_N_BORDER];

int checkIntersection(double dis)
{
	for(int i = 0; i < n; ++ i) {
		nboarder[i] = border[i];
		Point vec = border[i].p2 - border[i].p1;
		vec = vec.rot90();
		vec = vec / vec.abs() * dis;
		nboarder[i].p1 = border[i].p1 + vec;
		nboarder[i].p2 = border[i].p2 + vec;
	}
	convexIntersection(nboarder);
	return calcArea();
}

int main() {
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		tp[i].read();
	}
	for (int i = 0; i < n; ++i) {
		int next = i == n - 1 ? 0 : i + 1;
		border[i].p1 = tp[i]; 
		border[i].p2 = tp[next];
		border[i].setAlpha();
	}

	double l = 0, r = 1e7, mid;
	//checkIntersection(1);
	for( ; l + 1e-4 < r; ) {
		mid = (l + r) * 0.5;
		if (checkIntersection(mid)) {
			l = mid;
		} else r = mid;
	}
	printf("%.4f\n", (l + r) * 0.5);
	return 0;
}
