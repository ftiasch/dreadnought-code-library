//sgu206
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
struct recmap
{
	int y, c;
	recmap *next;
} *p, ma1[1000], *id1[1001];
int n, m, l1, l2, c[1001], i, x, y, z, g[401][401], gn, ll[1001], lr[1001], rm[1001], exd, t;
bool f[1001], vl[1001];
void build(int x, int y)
{
	ma1[++l1].y = y;
	ma1[l1].next = id1[x];
	id1[x] = &ma1[l1];
}
bool dfs(int v)
{
	if(v == y) return true;
	f[v] = false;
	for(recmap *p=id1[v];p;p=p->next) if(f[p->y] and dfs(p->y))
	{
		g[(p-ma1)>>1][i-n+1] = c[(p-ma1)>>1]-z;
		return true;
	}
	return false;
}
int hgry(int v)
{

	vl[v] = true;
	for(int u = 1; u <= gn; u++)
		if(f[u]) 
		{
			if((t=ll[v]+lr[u] - g[v][u])==0)
			{
				f[u] = false;
				if(rm[u] == 0 or hgry(rm[u])) return rm[u] = v;
			}else exd = min(exd, t);
		}
	return 0;
}
void KM()
{
	memset(ll, 0x7f, sizeof(ll));
	memset(lr, 0, sizeof(lr));
	memset(rm, 0, sizeof(rm));
	for(int i = 1; i < n; i++)
	{
		for(;;)
		{
			memset(vl, false, sizeof(vl));
			memset(f, true, sizeof(f));
			exd = 0x7fffffff;
			if(hgry(i)) break;
			for(int i = 1; i < n; i++) if(vl[i]) ll[i] -= exd;
			for(int i = n; i <= m; i++) if(!f[i-n+1]) lr[i-n+1] += exd;
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(id1, 0, sizeof(id1));
	l1 = 1;
	for(i = 1; i < n; i++)
	{
		scanf("%d%d%d", &x, &y, &c[i]);
		build(x, y);
		build(y, x);
	}
	memset(g, 0, sizeof(g));
	for(i = n; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		c[i] = z;
		memset(f, true, sizeof(f));
		dfs(x);
	}
	gn = max(n-1, m-n+1);
	KM();
	for(int i = 1; i < n; i++) printf("%d\n", c[i]-ll[i]);
	for(int i = n; i <= m; i++) printf("%d\n", c[i] + lr[i-n+1]);
	return 0;
}
