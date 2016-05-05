#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

int sign(double x)
{
	return x < -EPS ? -1 : x > EPS;
}

double newSqrt(double x)
{
	return x < 0 ? 0 : sqrt(x);
}

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	Point operator + (const Point &that) const {
		return Point(x + that.x, y + that.y);
	}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	Point operator * (const double &that) const {
		return Point(x * that, y * that);
	}
	Point operator / (const double &that) const {
		return Point(x / that, y / that);
	}
	Point rotate(const double ang) { //逆时针旋转 ang 弧度
		return Point(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);
	}
	Point turn90() { //逆时针旋转 90 度
		return Point(-y, x);
	}
	double len2() const {
		return x * x + y * y;
	}
	double len() const {
		return sqrt(x * x + y * y);
	}
	Point unit() const {
		return *this / len();
	}
};
double det(Point a, Point b)
{
	return a.x * b.y - b.x * a.y;
}
double dot(Point a, Point b)
{
	return a.x * b.x + a.y * b.y;
}

struct Line {
	Point a, b;
	Line(Point a, Point b) : a(a), b(b) {}
};

Point isLL(const Line &l0, const Line &l1) {
	double s0 = det(l1.b - l1.a, l0.a - l1.a),
		   s1 = -det(l1.b - l1.a, l0.b - l1.a);
	return (l0.a * s1 + l0.b * s0) / (s0 + s1);
}
bool onSeg(const Line &l, const Point &p) { //点在线段上
	return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
Point projection(const Line &l, const Point &p) { //点到直线投影
	return l.a + (l.b - l.a) * (dot(p - l.a, l.b - l.a) / (l.b - l.a).len2());
}
double disToLine(const Line &l, const Point &p) {
	return abs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
double disToSeg(const Line &l, const Point &p) { //点到线段距离
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) != 1 ?
		disToLine(l, p) : min((p - l.a).len(), (p - l.b).len());
}
Point symmetryPoint(const Point a, const Point b) { //点 b 关于点 a 的中心对称点
	return a + a - b;
}
Point reflection(const Line &l, const Point &p) { //点关于直线的对称点
	return symmetryPoint(projection(l, p), p);
}
struct Circle {
	Point o;
	double r;
	Circle (Point o = Point(0, 0), double r = 0) : o(o), r(r) {}
};
// 求圆与直线的交点
bool isCL(Circle a, Line l, Point &p1, Point &p2) { 
	if (sign(det(l.a - a.o, l.b - a.o) / (l.a - l.b).len()) > 0) return false;
	Point o = isLL(Line(a.o, a.o + (l.b - l.a).turn90()), l);
	Point delta = (l.b - l.a).unit() * newSqrt(a.r * a.r - (o - a.o).len2());
	p1 = o + delta;
	p2 = o - delta;
	return true;
}

// 求圆与圆的交面积
double areaCC(const Circle &c1, const Circle &c2) {
	double d = (c1.o - c2.o).len();
	if (sign(d - (c1.r + c2.r)) > 0) {
		return 0;
	}
	if (sign(d - abs(c1.r - c2.r)) < 0) {
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

// 求点到圆的切点，按关于点的左手方向返回两个点
bool tanCP(const Circle &c, const Point &p0, Point &p1, Point &p2)
{
	double x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if (d < EPS) return false;
	Point p = (p0 - c.o) * (c.r * c.r / x);
	Point delta = ((p0 - c.o) * (-c.r * sqrt(d) / x)).turn90();
	p1 = c.o + p + delta;
	p2 = c.o + p - delta;
	return true;
}

// 求圆到圆的外共切线，按关于 c1.o 的左手方向返回两条线
vector<Line> extanCC(const Circle &c1, const Circle &c2)
{
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

// 求圆到圆的内共切线，按关于 c1.o 的左手方向返回两条线
vector<Line> intanCC(const Circle &c1, const Circle &c2)
{
	vector<Line> ret;
	Point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
	Point p1, p2, q1, q2;
	if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
		ret.push_back(Line(p1, q1));
		ret.push_back(Line(p2, q2));
	}
	return ret;
}


int main()
{
	return 0;
}
