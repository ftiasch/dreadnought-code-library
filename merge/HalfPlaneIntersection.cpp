struct Point {
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0);}
};
struct Line {
	bool include(const Point &p) const { return sign(det(b - a, p - a)) > 0; }
	Line push() const{ // 将半平面向外推 eps
		const double eps = 1e-6;
		Point delta = (b - a).turn90().norm() * eps;
		return Line(a - delta, b - delta);
	}
};
bool sameDir(const Line &l0, const Line &l1) { return parallel(l0, l1) && sign(dot(l0.b - l0.a, l1.b - l1.a)) == 1; }
bool operator < (const Point &a, const Point &b) {
	if (a.quad() != b.quad()) {
		return a.quad() < b.quad();
	} else {
		return sign(det(a, b)) > 0;
	}
}
bool operator < (const Line &l0, const Line &l1) {
	if (sameDir(l0, l1)) {
		return l1.include(l0.a);
	} else {
		return (l0.b - l0.a) < (l1.b - l1.a);
	}
}
bool check(const Line &u, const Line &v, const Line &w) { return w.include(intersect(u, v)); }
vector<Point> intersection(vector<Line> &l) {
	sort(l.begin(), l.end());
	deque<Line> q;
	for (int i = 0; i < (int)l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) {
			continue;
		}
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i])) q.pop_back();
		while (q.size() > 1 && !check(q[1], q[0], l[i])) q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
	while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1])) q.pop_front();
	vector<Point> ret;
	for (int i = 0; i < (int)q.size(); ++i) ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
	return ret;
}
