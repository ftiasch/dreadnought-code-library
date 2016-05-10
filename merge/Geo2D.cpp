struct Point {
	Point rotate(const double ang) { // 逆时针旋转 ang 弧度
		return Point(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);
	}
	Point turn90() { // 逆时针旋转 90 度
		return Point(-y, x);
	}
};
Point isLL(const Line &l1, const Line &l2) {
	double s1 = det(l2.b - l2.a, l1.a - l2.a),
		   s2 = -det(l2.b - l2.a, l1.b - l2.a);
	return (l1.a * s2 + l1.b * s1) / (s1 + s2);
}
bool onSeg(const Line &l, const Point &p) { // 点在线段上
	return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
Point projection(const Line &l, const Point &p) { // 点到直线投影
	return l.a + (l.b - l.a) * (dot(p - l.a, l.b - l.a) / (l.b - l.a).len2());
}
double disToLine(const Line &l, const Point &p) {
	return abs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
double disToSeg(const Line &l, const Point &p) { // 点到线段距离
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) != 1 ?
		disToLine(l, p) : min((p - l.a).len(), (p - l.b).len());
}
Point symmetryPoint(const Point a, const Point b) { // 点 b 关于点 a 的中心对称点
	return a + a - b;
}
Point reflection(const Line &l, const Point &p) { // 点关于直线的对称点
	return symmetryPoint(projection(l, p), p);
}
// 求圆与直线的交点
bool isCL(Circle a, Line l, Point &p1, Point &p2) { 
	double x = dot(l.a - a.o, l.b - l.a),
		y = (l.b - l.a).len2(),
		d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if (sign(d) < 0) return false;
	d = max(d, 0.0);
	Point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (sqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}
// 求圆与圆的交面积
double areaCC(const Circle &c1, const Circle &c2) {
	double d = (c1.o - c2.o).len();
	if (sign(d - (c1.r + c2.r)) >= 0) {
		return 0;
	}
	if (sign(d - abs(c1.r - c2.r)) <= 0) {
		double r = min(c1.r, c2.r);
		return r * r * PI;
	}
	double x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d),
		   t1 = acos(x / c1.r), t2 = acos((d - x) / c2.r);
	return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}
// 求圆与圆的交点，注意调用前要先判定重圆
bool isCC(Circle a, Circle b, Point &p1, Point &p2) { 
	double s1 = (a.o - b.o).len();
	if (sign(s1 - a.r - b.r) > 0 || sign(s1 - abs(a.r - b.r)) < 0) return false;
	double s2 = (a.r * a.r - b.r * b.r) / s1;
	double aa = (s1 + s2) * 0.5, bb = (s1 - s2) * 0.5;
	Point o = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	Point delta = (b.o - a.o).unit().turn90() * newSqrt(a.r * a.r - aa * aa);
	p1 = o + delta, p2 = o - delta;
	return true;
}
// 求点到圆的切点，按关于点的顺时针方向返回两个点
bool tanCP(const Circle &c, const Point &p0, Point &p1, Point &p2) {
	double x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if (d < EPS) return false; // 点在圆上认为没有切点
	Point p = (p0 - c.o) * (c.r * c.r / x);
	Point delta = ((p0 - c.o) * (-c.r * sqrt(d) / x)).turn90();
	p1 = c.o + p + delta;
	p2 = c.o + p - delta;
	return true;
}
// 求圆到圆的外共切线，按关于 c1.o 的顺时针方向返回两条线
vector<Line> extanCC(const Circle &c1, const Circle &c2) {
	vector<Line> ret;
	if (sign(c1.r - c2.r) == 0) {
		Point dir = c2.o - c1.o;
		dir = (dir * (c1.r / dir.len())).turn90();
		ret.push_back(Line(c1.o + dir, c2.o + dir));
		ret.push_back(Line(c1.o - dir, c2.o - dir));
	} else {
		Point p = (c1.o * -c2.r + c2.o * c1.r) / (c1.r - c2.r);
		Point p1, p2, q1, q2;
		if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
			if (c1.r < c2.r) swap(p1, p2), swap(q1, q2);
			ret.push_back(Line(p1, q1));
			ret.push_back(Line(p2, q2));
		}
	}
	return ret;
}
// 求圆到圆的内共切线，按关于 c1.o 的顺时针方向返回两条线
vector<Line> intanCC(const Circle &c1, const Circle &c2) {
	vector<Line> ret;
	Point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
	Point p1, p2, q1, q2;
	if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) { // 两圆相切认为没有切线
		ret.push_back(Line(p1, q1));
		ret.push_back(Line(p2, q2));
	}
	return ret;
}
bool contain(vector<Point> polygon, Point p) { // 判断点 p 是否被多边形包含，包括落在边界上
	int ret = 0, n = polygon.size();
	for(int i = 0; i < n; ++ i) {
		Point u = polygon[i], v = polygon[(i + 1) % n];
		if (onSeg(Line(u, v), p)) return true;
		if (sign(u.y - v.y) <= 0) swap(u, v);
		if (sign(p.y - u.y) > 0 || sign(p.y - v.y) <= 0) continue;
		ret += sign(det(p, v, u)) > 0;
	}
	return ret & 1;
}
vector<Point> convexCut(const vector<Point>&ps, Line l) { // 用半平面 (q1,q2) 的逆时针方向去切凸多边形
	vector<Point> qs; 
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = sign(det(l.a, l.b, p1)), d2 = sign(det(l.a, l.b, p2));
		if (d1 >= 0) qs.push_back(p1);
		if (d1 * d2 < 0) qs.push_back(isLL(Line(p1, p2), l));
	}
	return qs;
}
vector<Point> convexHull(vector<Point> ps) { // 求点集 ps 组成的凸包
	int n = ps.size(); if (n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<Point> qs;
	for (int i = 0; i < n; qs.push_back(ps[i++])) 
		while (qs.size() > 1 && sign(det(qs[qs.size()-2],qs.back(),ps[i])) <= 0) qs.pop_back();
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i--])) 
		while ((int)qs.size() > t && sign(det(qs[(int)qs.size()-2],qs.back(),ps[i])) <= 0) qs.pop_back();
	qs.pop_back(); return qs;
}
