#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 505;
const int inf = (int)1e9;
int cost[maxn][maxn],seq[maxn],len[maxn],n,m,pop,ans;
bool used[maxn];
void Init(){
	int i,j,a,b,c;
	for(i=0;i<n;i++) for(j=0;j<n;j++) cost[i][j]=0;
	for(i=0;i<m;i++){
		scanf("%d %d %d",&a,&b,&c); cost[a][b]+=c; cost[b][a]+=c;
	}
	pop=n; for(i=0;i<n;i++) seq[i]=i;
}
void Work(){
	ans=inf; int i,j,k,l,mm,sum,pk;
	while(pop > 1){
		for(i=1;i<pop;i++) used[seq[i]]=0; used[seq[0]]=1;
		for(i=1;i<pop;i++) len[seq[i]]=cost[seq[0]][seq[i]];
		pk=0; mm=-inf; k=-1;
		for(i=1;i<pop;i++) if(len[seq[i]] > mm){ mm=len[seq[i]]; k=i; }
		for(i=1;i<pop;i++){
			used[seq[l=k]]=1;
			if(i==pop-2) pk=k;
			if(i==pop-1) break;
			mm=-inf;
			for(j=1;j<pop;j++) if(!used[seq[j]])
				if((len[seq[j]]+=cost[seq[l]][seq[j]]) > mm)
					mm=len[seq[j]], k=j;
		}
		sum=0;
		for(i=0;i<pop;i++) if(i != k) sum+=cost[seq[k]][seq[i]];
		ans=min(ans,sum);
		for(i=0;i<pop;i++)
			cost[seq[k]][seq[i]]=cost[seq[i]][seq[k]]+=cost[seq[pk]][seq[i]];
		seq[pk]=seq[--pop];
	}
	printf("%d\n",ans);
}
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		Init(); Work();
	}
}
