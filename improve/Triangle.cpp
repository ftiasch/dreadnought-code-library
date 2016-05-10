Point inCenter(const Point &A, const Point &B, const Point &C) { // 内心
	double a = (B - C).len(), b = (C - A).len(), c = (A - B).len(),
		s = fabs(det(B - A, C - A)),
		r = s / p;
	return (A * a + B * b + C * c) / (a + b + c);
}
Point circumCenter(const Point &a, const Point &b, const Point &c) { // 外心
	Point bb = b - a, cc = c - a;
	double db = bb.len2(), dc = cc.len2(), d = 2 * det(bb, cc);
	return a - Point(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}
Point othroCenter(const Point &a, const Point &b, const Point &c) { // 垂心
	Point ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.y * ca.y * bc.y,
		   A = ca.x * ba.y - ba.x * ca.y,
		   x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
		   y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return Point(x0, y0);
}
