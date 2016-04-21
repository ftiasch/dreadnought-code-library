double calcDist(const Point &p, int a, int b, int c) {
	return fabs(mix(info[a] - p, info[b] - p, info[c] - p) / area(a, b, c));
}
//compute the minimal distance of center of any faces
double findDist() {
	//compute center of mass
	double totalWeight = 0;
	Point center(.0, .0, .0);
	Point first = info[face[0][0]];
	for (int i = 0; i < SIZE(face); ++i) {
		Point p = (info[face[i][0]] + info[face[i][1]] + info[face[i][2]] + first) * .25;
		double weight = mix(info[face[i][0]] - first, info[face[i][1]] - first, info[face[i][2]] - first); 
		totalWeight += weight;
		center = center + p * weight;
	}
	center = center / totalWeight;
	//compute distance 
	double res = 1e100;
	for (int i = 0; i < SIZE(face); ++i) {
		res = min(res, calcDist(center, face[i][0], face[i][1], face[i][2]));
	}
	return res;
}

