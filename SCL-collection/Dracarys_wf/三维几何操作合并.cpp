const double pi = acos(-1.0); double a[4][4];
int dcmp(const double &a, const double &b = 0, const double & zero = 1e-6){
	if (a - b < -zero)	return -1;	return a - b > zero;}
void multi(const double a[4][4],const double b[4][4],double c[4][4]){
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++){
		c[i][j]=a[i][0]*b[0][j]; 
		for(int k=1;k<4;k++) 
		c[i][j]+=a[i][k]*b[k][j];
	}}
void multi(double a[4][4],const double b[4][4]){
	static double c[4][4];
	multi(a,b,c);
	memcpy(a,c,sizeof(a[0][0])*16);
}
void Macro(){
	double b[4][4]={1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	memcpy(a,b,sizeof(a[0][0])*16);
}
void Translation(const Point_3 &s){
	double p[4][4]={1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, s.x, s.y, s.z, 1};
	multi(a,p);
}
void Scaling(const Point_3 &s){
	double p[4][4]={s.x, 0, 0, 0, 0, s.y, 0, 0, 0, 0, s.z, 0, 0, 0, 0, 1};
	multi(a,p);
}
void Rotate(const Point_3 &s, double r) {
	double l=s.Length();	double x=s.x/l,y=s.y/l,z=s.z/l;
	double SinA=sin(r),CosA=cos(r);
	double p[4][4]={CosA + (1 - CosA) * x * x, (1 - CosA) * x * y - SinA * z, (1 - CosA) * x * z + SinA * y, 0,(1 - CosA) * y * x + SinA * z,
		CosA + (1 - CosA) * y * y, (1 - CosA) * y * z - SinA * x, 0,
		(1 - CosA) * z * x - SinA * y, (1 - CosA) * z * y + SinA * x, CosA + (1 - CosA) * z * z, 0, 0, 0, 0, 1};
	multi(a,p);
}
Point_3 opt(const Point_3&s){
	double x,y,z;
	return Point_3( s.x * a[0][0] + s.y * a[1][0] + s.z * a[2][0] + a[3][0],
	s.x * a[0][1] + s.y * a[1][1] + s.z * a[2][1] + a[3][1],
	s.x * a[0][2] + s.y * a[1][2] + s.z * a[2][2] + a[3][2]);
}
int main(){
	Macro();
	int n;for (scanf("%d", &n); n; n--) {
		char c;	Point_3 p;
		scanf("\n%c%lf%lf%lf", &c, &p.x, &p.y, &p.z);
		if (c == 'T') Translation(p);	if (c == 'S') Scaling(p);
		if (c == 'R') {	double r;scanf("%lf\n", &r);
			Rotate(p, r);	//===========绕OP逆时针旋转r角度
		}}
	for (scanf("%d", &n); n; n--) {
		Point_3 p, p2;	scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
		p2 = opt(p); 	printf(“%f %f %f\n”,p2.x,p2.y,p2.z);
	}}
