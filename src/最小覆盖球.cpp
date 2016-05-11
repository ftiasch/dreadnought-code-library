// 注意，无法处理小于四点的退化情况
int nouter; Tpoint outer[4], res; double radius;
void ball() {
	Tpoint q[3]; double m[3][3], sol[3], L[3], det;
	int i,j; res.x = res.y = res.z = radius = 0;
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
}
