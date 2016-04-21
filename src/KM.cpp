const int maxn=200;const int oo=0x7fffffff;
int w[maxn][maxn],x[maxn],y[maxn],px[maxn],py[maxn],sy[maxn],slack[maxn];
int par[maxn];int n;int pa[200][2],pb[200][2],n0,m0,na,nb;char s[200][200];
void adjust(int v){	sy[v]=py[v]; if (px[sy[v]]!=-2) adjust(px[sy[v]]);}
bool find(int v){for (int i=0;i<n;i++)
	if (py[i]==-1){
		if (slack[i]>x[v]+y[i]-w[v][i]) slack[i]=x[v]+y[i]-w[v][i],	par[i]=v;
		if (x[v]+y[i]==w[v][i]){
			py[i]=v; if (sy[i]==-1){adjust(i);	return 1;}
			if (px[sy[i]]!=-1) continue;	px[sy[i]]=i;
			if (find(sy[i])) return 1;
		}}return 0;}
int km(){int i,j,m,flag; for (i=0;i<n;i++) sy[i]=-1,y[i]=0;
	for (i=0;i<n;i++) {x[i]=0; for (j=0;j<n;j++) x[i]=max(x[i],w[i][j]);}
	for (i=0;i<n;i++){
		for (j=0;j<n;j++) px[j]=py[j]=-1,slack[j]=oo;
		px[i]=-2;	if (find(i)) continue; flag=false;
		for (;!flag;){ m=oo; 
		    for (j=0;j<n;j++) if (py[j]==-1) m=min(m,slack[j]);
			for (j=0;j<n;j++){ if (px[j]!=-1) x[j]-=m; 
			    if (py[j]!=-1) y[j]+=m; else slack[j]-=m;}
				for (j=0;j<n;j++){ if (py[j]==-1&&!slack[j]){
						py[j]=par[j];
						if (sy[j]==-1){	adjust(j);	flag=true;	break;}
						px[sy[j]]=j;	 if (find(sy[j])){flag=true;break;}
					}}}}
				int ans=0; for (i=0;i<n;i++) ans+=w[sy[i]][i];return ans;}
