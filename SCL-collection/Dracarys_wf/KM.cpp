int n,b[MAXN],dx[MAXN],dy[MAXN],slack[MAXN],a[MAXN][MAXN];
bool f[MAXN],g[MAXN];
bool hungary(int x)
{
	if (!x)
	return(true);
	f[x]=true;
	for (int i=1;i<=n;i++)
	{
		if (g[i])
		continue;
		int t=dx[x]+dy[i]-a[x][i];
		if (!t)
		{
			g[i]=true;
			if (hungary(b[i]))
			{
				b[i]=x;
				return(true);
			}
		}
		else if (t<slack[i])
		slack[i]=t;
	}
	return(false);
}
int main()
{
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	{
		scanf("%d",&a[i][j]);
		if (a[i][j]>dx[i])
		dx[i]=a[i][j];
	}
	for (int i=1;i<=n;i++)
	{
		memset(slack,63,sizeof(slack));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		while (!hungary(i))
		{
			int d=inf;
			for (int i=1;i<=n;i++)
			if (!g[i] && slack[i]<d)
			d=slack[i];
			for (int i=1;i<=n;i++)
			{
				if (f[i])
				dx[i]-=d;
				if (g[i])
				dy[i]+=d;
			}
			memset(f,0,sizeof(f));
			memset(g,0,sizeof(g));
		}
	}
}
