double areaCT(Point pa, Point pb, double r) {
	if (pa.len() < pb.len()) swap(pa, pb);
	if (sign(pb.len()) == 0) return 0;
	double a = pb.len(), b = pa.len(), c = (pb - pa).len();
	double sinB = fabs(det(pb, pb - pa) / a / c),
		   cosB = dot(pb, pb - pa) / a / c, 
		   sinC = fabs(det(pa, pb) / a/ b),
		   cosC = dot(pa, pb) / a / b;
	double B = atan2(sinB, cosB), C = atan2(sinC, cosC);
	if (a > r) {
		S = C / 2 * r * r;
		h = a * b * sinC / c;
		if (h < r && B < PI / 2) {
			S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
		}
	} else if (b > r) {
		double theta = PI - B - asin(sinB / r * a);
		S = a * r * sin(theta) / 2 + (C - theta) / 2 * r * r;
	} else {
		S = sinC * a * b / 2;
	}
	return S;
}
