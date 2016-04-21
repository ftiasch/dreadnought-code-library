#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

struct Tpoint {
	double x, y, z;
	Tpoint(){}
	Tpoint(double x, double y, double z) : 
		x(x), y(y), z(z) {}
};
Tpoint operator + (const Tpoint&a, const Tpoint&b) {
	return Tpoint(a.x + b.x, a.y + b.y, a.z + b.z);
}
Tpoint operator - (const Tpoint&a, const Tpoint&b) {
	return Tpoint(a.x - b.x, a.y - b.y, a.z - b.z);
}
Tpoint operator * (const Tpoint&a, const double&b) {
	return Tpoint(a.x * b, a.y * b, a.z * b);
}
Tpoint operator / (const Tpoint&a, const double&b) {
	return Tpoint(a.x / b, a.y / b, a.z / b);
}
double dot (const Tpoint&a, const Tpoint&b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

const double eps = 1e-15;

double dist2 (const Tpoint&a, const Tpoint&b) {
	return dot(a - b, a - b);
}

int npoint, nouter; Tpoint pt[200000], outer[4],res; double radius,tmp;
void ball() {
	Tpoint q[3]; double m[3][3], sol[3], L[3], det;
	int i,j; res.x = res.y = res.z = radius = 0;
	switch ( nouter ) {
	case 1: res=outer[0]; break;
	case 2: res=(outer[0]+outer[1])/2; radius=dist2(res, outer[0]); break;
	case 3:
		for (i=0; i<2; ++i) q[i]=outer[i+1]-outer[0]; 
		for (i=0; i<2; ++i) for(j=0; j<2; ++j) m[i][j]=dot(q[i], q[j])*2;
		for (i=0; i<2; ++i) sol[i]=dot(q[i], q[i]);
		if (fabs(det=m[0][0]*m[1][1]-m[0][1]*m[1][0])<eps) return;
		L[0]=(sol[0]*m[1][1]-sol[1]*m[0][1])/det;
		L[1]=(sol[1]*m[0][0]-sol[0]*m[1][0])/det;
		res=outer[0]+q[0]*L[0]+q[1]*L[1];
		radius=dist2(res, outer[0]);
		break;
	case 4:
		for (i=0; i<3; ++i) q[i]=outer[i+1]-outer[0], sol[i]=dot(q[i], q[i]);
		for (i=0;i<3;++i) for(j=0;j<3;++j) m[i][j]=dot(q[i],q[j])*2;
		det= m[0][0]*m[1][1]*m[2][2]
		+ m[0][1]*m[1][2]*m[2][0]
		+ m[0][2]*m[2][1]*m[1][0]
		- m[0][2]*m[1][1]*m[2][0]
		- m[0][1]*m[1][0]*m[2][2]
		- m[0][0]*m[1][2]*m[2][1];
		if ( fabs(det)<eps ) return;
		for (j=0; j<3; ++j) {
			for (i=0; i<3; ++i) m[i][j]=sol[i];
			L[j]=( m[0][0]*m[1][1]*m[2][2]
			+ m[0][1]*m[1][2]*m[2][0]
			+ m[0][2]*m[2][1]*m[1][0]
			- m[0][2]*m[1][1]*m[2][0]
			- m[0][1]*m[1][0]*m[2][2]
			- m[0][0]*m[1][2]*m[2][1]
			) / det;
			for (i=0; i<3; ++i) m[i][j]=dot(q[i], q[j])*2;
		} res=outer[0];
		for (i=0; i<3; ++i ) res = res + q[i] * L[i];
		radius=dist2(res, outer[0]);
}}
void minball(int n) { ball();
	if ( nouter<4 ) for (int i=0; i<n; ++i)
	if (dist2(res, pt[i])-radius>eps) {
		outer[nouter++]=pt[i]; minball(i); --nouter;
		if (i>0) { Tpoint Tt = pt[i];
			memmove(&pt[1], &pt[0], sizeof(Tpoint)*i); pt[0]=Tt;
}}}
int main0(){
	for (int i=0;i<npoint;i++) scanf("%lf%lf%lf",&pt[i].x,&pt[i].y,&pt[i].z);
	random_shuffle(pt,pt+npoint); radius=-1;
	for (int i=0;i<npoint;i++) if (dist2(res,pt[i])-radius>eps)
		nouter=1, outer[0]=pt[i], minball(i);
	printf("%.5f\n",sqrt(radius));
}
int main() {
	while (scanf("%d", &npoint) == 1 && npoint) main0();
	return 0;
}
