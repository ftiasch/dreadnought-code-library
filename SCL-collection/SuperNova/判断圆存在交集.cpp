int n;
double sx, sy, d;
vector<Point> cir;
vector<double> radius;

int isIntersectCircleToCircle(Point c1, double r1, Point c2, double r2)
{
	double dis = c1.distTo(c2);
	return sign(dis - (r1 + r2)) <= 0;
}

void getRange(double x, Point &c, double r, double &retl, double &retr)
{
	double tmp = sqrt(max(r * r - (c.x - x) * (c.x - x), 0.0));
	retl = c.y - tmp; retr = c.y + tmp;
}

int checkInLine(double x)
{
	double minR = INF, maxL = -INF;
	double tmpl, tmpr;
	for(int i = 0; i < n; ++ i) {
		if (sign(cir[i].x + radius[i] - x) < 0 || sign(cir[i].x - radius[i] - x) > 0) 
			return false;
		getRange(x, cir[i], radius[i], tmpl, tmpr);
		maxL = max(tmpl, maxL);
		minR = min(tmpr, minR);
		if (maxL > minR) return false;
	}
	return true;
}

int shouldGoLeft(double x)
{
	if (checkInLine(x)) return 2;
	int onL = 0, onR = 0;
	for(int i = 0; i < n; ++ i) {
		if (sign(cir[i].x + radius[i] - x) < 0) onL = 1;
		if (sign(cir[i].x - radius[i] - x) > 0) onR = 1;
	}
	if (onL && onR) return -1;
	if (onL) return 1;
	if (onR) return 0;

	double minR = INF, maxL = -INF, tmpl, tmpr;
	int idMinR, idMaxL;

	for(int i = 0; i < n; ++ i) {
		getRange(x, cir[i], radius[i], tmpl, tmpr);
		if (tmpr < minR) {
			minR = tmpr;
			idMinR = i;
		}
		if (tmpl > maxL) {
			maxL = tmpl;
			idMaxL = i;
		}
	}
	if (! isIntersectCircleToCircle(cir[idMinR], radius[idMinR], cir[idMaxL], radius[idMaxL])) 
		return -1;
	Point p1, p2;
	intersectionCircleToCircle(cir[idMinR], radius[idMinR], cir[idMaxL], radius[idMaxL], p1, p2); 
	return (p1.x < x);
}

int hasIntersectionCircles()
{
	double l = -INF, r = INF, mid;
	for(int i = 0; i < 100; ++ i) {
		mid = (l + r) * 0.5;
		int tmp = shouldGoLeft(mid);
		if (tmp < 0) return 0;
		if (tmp == 2) return 1;
		if (tmp) r = mid;
		else l = mid;
	}
	mid = (l + r) * 0.5;
	return checkInLine(mid);
}
