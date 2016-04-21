struct Tree(){}*root[N];
int father[N],size[N],depth[N];
int bfsOrd[N],pathId[N],ordInPath[N],sqn[N];
void doBfs(int s){
	int qh=0,qt=0,*que=bfsOrd; father[s]=-1; depth[s]=0;
	for(que[qt++]=s;qh<qt;){
		int u=que[qh++];
		foreach(iter,adj[u]){
			int v=*iter; if(v==father[u]) continue;
			father[v]=u; depth[v]=depth[u]+1; que[qt++]=v;
		}
	}
}
void doSplit(){
	for(int i=N-1;i>=0;--i){
		int u=bfsOrd[i]; size[u]=1;
		foreach(iter,adj[u]){
			int v=*iter; if(v==father[u]) continue; size[u]+=size[v];
		}
	}
	memset(pathId,-1,sizeof pathId);
	for(int i=0;i<N;++i){
		int top=bfsOrd[i],cnt=0;
		if(pathId[top]!=-1) continue;
		for(int next,u=top;u!=-1;u=next){
			sqn[cnt]=val[u]; ordInPath[u]=cnt; pathId[u]=top; ++cnt;
			next=-1;
			foreach(iter,adj[u]){
				int v=*iter; if(v==father[u]) continue;
				if(next<0||size[next]<size[v]) next=v;
			}
		}
		root[top]=new Tree(0,cnt,sqn);
	}
}
void prepare(){ doBfs(0); doSplit(); }