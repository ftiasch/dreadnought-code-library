// Q is a priority_queue<PII, vector<PII>, greater<PII> >
// for an edge(s, t): u is the capacity, v is the cost, nxt is the next edge,
// op is the opposite edge
// this code can not deal with negative cycles
typedef pair<int,int> PII; 
struct edge{ int t,u,v; edge *nxt,*op; }E[MAXE],*V[MAXV];
int D[MAXN], dist[MAXN], maxflow, mincost; bool in[MAXN];
bool modlabel(){
	while(!Q.empty()) Q.pop();
	for(int i=S;i<=T;++i) if(in[i]) D[i]=0,Q.push(PII(0,i)); else D[i]=inf;
	while(!Q.empty()){
		int x=Q.top().first,y=Q.top().second; Q.pop();
		if(y==T) break; if(D[y]<x) continue;
		for(edge *ii=V[y];ii;ii=ii->nxt) if(ii->u)
			if(x+(ii->v+dist[ii->t]-dist[y])<D[ii->t]){
				D[ii->t]=x+(ii->v+dist[ii->t]-dist[y]);
				Q.push(PII(D[ii->t],ii->t));
			}
	}
	if(D[T]==inf) return false;
	for(int i=S;i<=T;++i) if(D[i]>D[T]) dist[i]+=D[T]-D[i];
	return true;
}
int aug(int p,int limit){
	if(p==T) return maxflow+=limit,mincost+=limit*dist[S],limit;
	in[p]=1; int kk,ll=limit;
	for(edge *ii=V[p];ii;ii=ii->nxt) if(ii->u){
		if(!in[ii->t]&&dist[ii->t]+ii->v==dist[p]){
			kk=aug(ii->t,min(ii->u,ll)); ll-=kk,ii->u-=kk,ii->op->u+=kk;
			if(!ll) return in[p]=0,limit;
		}
	}
	return limit-ll;
}
PII mincostFlow(){
	for(int i=S;i<=T;++i) dist[i]=i==T?inf:0;
	while(!Q.empty()) Q.pop(); Q.push(PII(0,T));
	while(!Q.empty()){
		int x=Q.top().first,y=Q.top().second; Q.pop(); if(dist[y]<x) continue;
		for(edge *ii=V[y];ii;ii=ii->nxt) if(ii->op->u&&ii->v+x<dist[ii->t]
			dist[ii->t]=ii->v+x,Q.push(PII(dist[ii->t],ii->t));
	}
	maxflow=mincost=0;
	do{
		do{
			memset(in,0,sizeof(in));
		}while(aug(S,maxflow));
	}while(modlabel());
	return PII(maxflow,mincost);
}

