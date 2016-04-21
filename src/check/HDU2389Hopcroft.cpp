#include <cstdio>
#include <cstring>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = 3010;
const int maxm = maxn * maxn;

int from[maxn],wh[maxn],g[maxn];
int num[maxm],nxt[maxm],tot;
int n,m,ans,h,t,q[maxn],dx[maxn],dy[maxn];
bool bfs(){
	bool ret=false;
	h=0;t=0;
	for(int i=0;i<n;i++) if(wh[i]==-1) t++, q[t]=i;
	memset(dx,0,sizeof(dx)), memset(dy,0,sizeof(dy));
	while(h++<t){
		for(int i=g[q[h]];i!=0;i=nxt[i])
			if(dy[num[i]]==0){
				dy[num[i]]=dx[q[h]]+1;
				if(from[num[i]]==-1) ret=true;
				else{
					dx[from[num[i]]]=dx[q[h]]+2;
					q[++t]=from[num[i]];
				}
			}
	}
	return ret;
}
bool dfs(int x){
	for(int i=g[x];i!=0;i=nxt[i]){
		if(dy[num[i]]==dx[x]+1){
			dy[num[i]]=0;
			if(from[num[i]]==-1||dfs(from[num[i]])){
				wh[x]=num[i];from[num[i]]=x;return true;
			}
		}
	}
	return false;
}
void hopcroft(){
	memset(from,-1,sizeof(from)), memset(wh,-1,sizeof(wh));
	while(bfs())
		for(int i=0;i<n;i++)
			if(wh[i]==-1&&dfs(i)) ans++;
}
void insert(int x,int y){ tot++;num[tot]=y;nxt[tot]=g[x];g[x]=tot; }

#define SQR(X) ((X)*(X))
int x[maxn * 2], y[maxn * 2], s[maxn];
int main(){
	int t, T;
	scanf("%d", &T);
	REP(CNT, T) {
		scanf("%d%d", &t, &n);
		REP(i, n) scanf("%d%d%d", &x[i], &y[i], &s[i]);
		scanf("%d", &m);
		REP(i, m) scanf("%d%d", &x[n + i], &y[n + i]);
		tot=0; memset(g,0,sizeof(g));
		REP(i, n) REP(j, m) if (SQR(t * s[i]) >= SQR(x[i] - x[n + j]) + SQR(y[i] - y[n + j]))
			insert(i, j);
		ans=0; hopcroft(); 
		printf("Scenario #%d:\n%d\n\n",CNT+1, ans);
	}
}

