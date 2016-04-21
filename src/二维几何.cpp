inline int sign(const double &a) {return a < -EPS ? -1 : a > EPS;}
inline double newSqrt(const double &x) {return x < 0 ? 0 : sqrt(x);}
struct Point {
	double x, y;
	Point() {}
	Point(double _x, double _y) : x(_x), y(_y) {}
	Point operator+(const Point&p) const { return Point(x + p.x, y + p.y); }
	Point operator-(const Point&p) const { return Point(x - p.x, y - p.y); }
	Point operator*(double d) const { return Point(x * d, y * d); }
	Point operator/(double d) const { return Point(x / d, y / d); }
	bool operator<(const Point&p) const { int c = sign(x - p.x); if (c) return c == -1; return sign(y - p.y) == -1; }
	double dot(const Point&p) const { return x * p.x + y * p.y; }
	double det(const Point&p) const { return x * p.y - y * p.x; }
	Point rotAlpha(const double &alpha, const Point &o = Point(0, 0)) const { // 顺时针方向旋转 alpha
		double nx = cos(alpha) * (x - o.x) + sin(alpha) * (y - o.y);
		double ny = -sin(alpha) * (x - o.x) + cos(alpha) * (y - o.y);
		return Point(nx, ny) + o;
	}
	Point rot90() const { return Point(-y, x); }
	Point unit() { return *this / abs(); }
	double abs() { return hypot(x, y); }
	double abs2() { return x * x + y * y; }
};
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))
Point isSS(Point p1, Point p2, Point q1, Point q2) { // 直线与直线求交点，需要预判直线不平行
	double a1 = cross(q1,q2,p1), a2 = -cross(q1,q2,p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}
bool inSeg(Point u, Point v, Point p) { // 判断点在线段上，包括与端点重合
	return sign((u - p).det(v - p)) == 0 && sign((u - p).dot(v - p)) <= 0;
}
double distPL(Point p, Point u, Point v) { // 求点 p 到直线 (u,v) 的距离
	return abs((u - p).det(v - p)) / (u - v).abs();
}
struct Circle {
	Point o; double r;
	bool contain(const Circle &that, const int &c) const { 
		return sign(r - (o - that.o).abs() - that.r) > c;
	}
	bool disjuct(const Circle &that, const int &c) const { // c=0 为严格 , c=-1 为不严格
		return sign((o - that.o).abs() - r - that.r) > c;
	}
};
bool isCL(Circle a, Point l1, Point l2, Point &p1, Point &p2) { // 求圆与直线的交点，包含相切
	if (sign(distPL(a.o, l1, l2) - a.r) > 0) return false;
	Point o2 = a.o + (l2 - l1).rot90(); o2 = isSS(a.o, o2, l1, l2);
	double t = newSqrt(a.r * a.r - (o2 - a.o).abs2());
	p1 = o2 + (l2 - l1).unit() * t, p2 = o2 - (l2 - l1).unit() * t;
	return true;
}
bool isCC(Circle a, Circle b, Point &p1, Point &p2) { // 求圆与圆的交点，包含相切，假设无重圆
	if (a.contain(b, 0) || b.contain(a, 0) || a.disjuct(b, 0)) return false;
	double s1 = (a.o - b.o).abs();
	double s2 = (a.r * a.r - b.r * b.r) / s1;
	double aa = (s1 + s2) / 2, bb = (s1 - s2) / 2;
	Point mm = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	double h = newSqrt(a.r * a.r - aa * aa);
	Point vv = (b.o - a.o).unit().rot90() * h;
	p1 = mm + vv, p2 = mm - vv;
	return true;
}
bool contain(vector<Point> polygon, Point p) { // 判断点 p 是否被 多边形包含，包括落在边界上
	int ret = 0, n = polygon.size();
	for(int i = 0; i < n; ++ i) {
		Point u = polygon[i], v = polygon[(i + 1) % n];
		if (inSeg(u, v, p)) return true;
		if (sign(u.y - v.y) <= 0) swap(u, v);
		if (sign(p.y - u.y) > 0 || sign(p.y - v.y) <= 0) continue;
		ret += sign((v - p).det(u - p)) > 0;
	}
	return ret & 1;
}
vector<Point> convexCut(const vector<Point>&ps, Point q1, Point q2) { // 用半平面 (q1,q2) 的逆时针方向去切凸多边形
	vector<Point> qs; int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
		if (d1 >= 0) qs.push_back(p1);
		if (d1 * d2 < 0) qs.push_back(isSS(p1, p2, q1, q2));
	}
	return qs;
}
vector<Point> convexHull(vector<Point> ps) { // 求点集 ps 组成的凸包
	int n = ps.size(); if (n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<Point> qs;
	for (int i = 0; i < n; qs.push_back(ps[i++])) 
		while (qs.size() > 1 && crossOp(qs[qs.size()-2],qs.back(),ps[i]) <= 0) qs.pop_back();
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i--])) 
		while ((int)qs.size() > t && crossOp(qs[(int)qs.size()-2],qs.back(),ps[i]) <= 0) qs.pop_back();
	qs.pop_back(); return qs;
}
double convexDiameter(const vector<Point>&ps) { // 求凸包 ps 的最远点对距离
	int n = ps.size(), is = 0, js = 0;
	for (int i = 1; i < n; ++i) {
		if (ps[i].x > ps[is].x) is = i;
		if (ps[i].x < ps[js].x) js = i;
	}
	double maxd = (ps[is] - ps[js]).abs();
	int i = is, j = js;
	do {
		if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0) (++j) %= n;
		else (++i) %= n;
		maxd = max(maxd, (ps[i] - ps[j]).abs());
	} while (i != is || j != js);
	return maxd;
}
