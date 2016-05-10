ULL A,B,p[maxn],q[maxn],a[maxn],g[maxn],h[maxn];
int main() {
	for (int test=1, n;scanf("%d",&n) && n;++test) {
		printf("Case %d: ",test);
		if (fabs(sqrt(n)-floor(sqrt(n)+1e-7))<=1e-7)   {
			int a=(int)(floor(sqrt(n)+1e-7)); printf("%d %d\n",a,1);
		} else {
			// 求 $x^2-ny^2=1$ 的最小正整数根, n 不是完全平方数 
			p[1]=q[0]=h[1]=1;p[0]=q[1]=g[1]=0;
			a[2]=(int)(floor(sqrt(n)+1e-7));
			for (int i=2;i;++i) {
				g[i]=-g[i-1]+a[i]*h[i-1]; h[i]=(n-sqr(g[i]))/h[i-1];
				a[i+1]=(g[i]+a[2])/h[i]; p[i]=a[i]*p[i-1]+p[i-2];
				q[i]=a[i]*q[i-1]+q[i-2];
				if (sqr((ULL)(p[i]))-n*sqr((ULL)(q[i]))==1){
					A=p[i];B=q[i];break; 
				}
			} 
			cout << A << ' ' << B <<endl;
		}
	}
}
