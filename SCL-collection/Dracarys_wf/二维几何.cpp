struct Point {
	Point Rotate(double a) const {
		return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
};
bool Line_Intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &e) {
	double s1 = Det(c - a, d - a);
	double s2 = Det(d - b, c - b);
	if (!Sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return 1;
}
int Side(const Point &a, const Point &b, const Point &c) {
	return Sign(Det(c - a, b - a));
}
bool In_The_Seg(const Point &a, const Point &b, const Point &c) {
	if (Sign(Dist(a, b, c))) return 0;// Not needed when you make sure it does technically.
	return Sign(Dot(a - c, b - c)) <= 0;
}
bool Seg_Intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &e) {
	double s1 = Det(c - a, d - a);
	double s2 = Det(d - b, c - b);
	if (!Sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return In_The_Seg(a, b, e) && In_The_Seg(c, d, e);
}
struct Circle {
	Point o;
	double r;//  Squared
	bool Inside(Point a) {
		return Sqr(a.x - o.x) + Sqr(a.y - o.y) <= r;
	}
	void Calc(Point a, Point b) {
		o.x = (a.x + b.x) / 2;
		o.y = (a.y + b.y) / 2;
		r = Sqr(a.x - o.x) + Sqr(a.y - o.y);
	}
	void Calc(Point a, Point b, Point c) {// Not certain if a, b and c lie in the same line, which needs prejudging.
		double a1 = 2 * (a.x - b.x);
		double b1 = 2 * (a.y - b.y);
		double c1 = Sqr(a.x) - Sqr(b.x) + Sqr(a.y) - Sqr(b.y);
		double a2 = 2 * (a.x - c.x);
		double b2 = 2 * (a.y - c.y);
		double c2 = Sqr(a.x) - Sqr(c.x) + Sqr(a.y) - Sqr(c.y);
		o.x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
		o.y = (c1 * a2 - c2 * a1) / (a2 * b1 - a1 * b2);
		r = Sqr(a.x - o.x) + Sqr(a.y - o.y);
	}
	bool Intersect_With_Line(Point fr, Point to, Point &A, Point &B) const {
		if (Sign(Det(o - fr, to - fr)) > 0) swap(fr, to);
		double R = Sqrt(r);
		double h = Dist(fr, to, o);
		if (Sign(h - R) > 0) return 0;
		Point mm = (to - fr).Unit().Rotate(-pi / 2) * h + o;
		double l = Sqrt(Sqr(R) - Sqr(h));
		Point vv = (to - fr).Unit() * l;
		A = mm - vv;
		B = mm + vv;
		return 1;
	}
	bool Contain(const Circle &a) const {// Not tested
		return Sign(Sqrt(a.r) + (o - a.o).Length() - Sqrt(r)) < 0;
	}
	bool Disjunct(const Circle &a) const {// Not tested
		return Sign(Sqrt(a.r) + Sqrt(r) - (o - a.o).Length()) < 0;
	}
};
bool Intersect(Circle a, Circle b, Point &A, Point &B) {// Not tested, and must take care if a and b are the same one
	if (a.Contain(b) || b.Contain(a) || a.Disjunct(b)) return 0;
	double s1 = (a.o - b.o).Length();
	double s2 = (a.r - b.r) / s1;
	double aa = (s1 + s2) / 2;
	double bb = (s1 - s2) / 2;
	Point mm = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	double h = Sqrt(a.r - Sqr(aa));
	Point vv = (b.o - a.o).Unit().Rotate(pi / 2) * h;
	A = mm + vv;
	B = mm - vv;
	return 1;
}
struct Polygon {
	Point list[maxn];
	int n;
	Polygon() {
	}
	Polygon(const Polygon &a) {
		n = a.n;
		int i;
		for (i = 0; i < n; i++)
		list[i] = a.list[i];
	}
	Polygon &operator = (const Polygon &a) {
		if (this == &a) return *this;
		n = a.n;
		int i;
		for (i = 0; i < n; i++)
		list[i] = a.list[i];
		return *this;
	}
	Polygon Cut(const Point &a, const Point &b) {
		static Polygon res;
		res.n = 0;
		int i, s1, s2;
		Point curr;
		for (i = 0; i < n; i++) {
			s1 = Sign(Det(list[i] - a, b - a));
			s2 = Sign(Det(list[(i + 1) % n] - a, b - a));
			if (s1 <= 0) res.list[res.n++] = list[i];
			if (s1 * s2 < 0) {
				Line_Intersect(a, b, list[i], list[(i + 1) % n], curr);
				res.list[res.n++] = curr;
			}
		}
		return res;
	}
	Polygon Strict_Cut(const Point &fr, const Point &to) const {
		static Polygon res;
		res.n = 0;
		int i, s1, s2;
		Point a, b;
		for (i = 0; i < n; i++)
		if (Side(fr, to, list[i]) < 0) break;
		if (i == n) return res;
		Point c;
		for (i = 0; i < n; i++) {
			a = list[i];
			b = list[(i + 1) % n];
			s1 = Side(fr, to, a);
			s2 = Side(fr, to, b);
			if (s1 <= 0) res.list[res.n++] = a;
			if (s1 * s2 < 0) {
				Line_Intersect(fr, to, a, b, c);
				res.list[res.n++] = c;
			}
		}
		return res;
	}
	bool Contain(const Point &curr) const {
		int i, res = 0;
		Point A, B;
		for (i = 0; i < n; i++) {
			A = list[i];
			B = list[(i + 1) % n];
			if (In_The_Seg(A, B, curr)) return 1;
			if (Sign(A.y - B.y) <= 0) swap(A, B);
			if (Sign(curr.y - A.y) > 0) continue;
			if (Sign(curr.y - B.y) <= 0) continue;
			res += Sign(Det(B - curr, A - curr)) > 0;
		}
		return res & 1;
	}
};
