point ORI;
double r;
int n;
point info[maxn];
//用有向面积，划分成一个三角形和圆的面积的交 
double area2(point pa, point pb) {
	if (pa.len() < pb.len()) swap(pa, pb);
	if (pb.len() < eps) return 0;
	double a, b, c, B, C, sinB, cosB, sinC, cosC, S, h, theta;
	a = pb.len();
	b = pa.len();
	c = (pb - pa).len();
	cosB = dot(pb, pb - pa) / a / c;
	B = acos(cosB);
	cosC = dot(pa, pb) / a / b;
	C = acos(cosC);
	if (a > r) {
		S = (C/2)*r*r;
		h = a*b*sin(C)/c;
		if (h < r && B < PI/2) S -= (acos(h/r)*r*r - h*sqrt(r*r-h*h));
	} else if (b > r) {
		theta = PI - B - asin(sin(B)/r*a);
		S = .5*a*r*sin(theta) + (C-theta)/2*r*r;
	} else {
		S = .5*sin(C)*a*b;
	}
	//printf("res = %.4f\n", S);
	return S;
}
double area() {
	double S = 0;
	for (int i = 0; i < n; ++i) {
		S += area2(info[i], info[i + 1]) * Sign(cross(info[i], info[i + 1]));
	}
	return fabs(S);
}
