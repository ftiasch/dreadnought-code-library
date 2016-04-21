int from[1010], wh[1010], g[1010];
int num[100010], nxt[100010], tot;
int n, m, ans, h, t, q[1010], dx[1010], dy[1010];
bool bfs(){
	bool ret=false;
	h=0; t=0;
	for ( int i=0; i<n; i++ )
		if ( wh[i]==-1 ){
			t++; q[t]=i;
		}
	memset( dx, 0, sizeof( dx ) );
	memset( dy, 0, sizeof( dy ) );
	while ( h<t ){
		h++;
		for ( int i=g[q[h]]; i!=0; i=nxt[i] )
			if ( dy[num[i]]==0 ){
				dy[num[i]]=dx[q[h]]+1;
				if ( from[num[i]]==-1 )
					ret=true;
				else {
					dx[from[num[i]]]=dx[q[h]]+2;
					t++; q[t]=from[num[i]];
				}
			}
	}
	return ret;
}
bool dfs( int x ){
	for ( int i=g[x]; i!=0; i=nxt[i] ){
		if ( dy[num[i]]==dx[x]+1 ){
			dy[num[i]]=0;
			if ( from[num[i]]==-1 || dfs( from[num[i]] ) ){
				wh[x]=num[i]; from[num[i]]=x; return true;
			}
		}
	}
	return false;
}
void hopcroft(){
	memset( from, -1, sizeof( from ) );
	memset( wh, -1, sizeof( wh ) );
	while ( bfs() ){
		for ( int i=0; i<n; i++ )
			if ( wh[i]==-1 && dfs(i) ) ans++;
	}
}
void insert( int x, int y ){
	tot++; num[tot]=y; nxt[tot]=g[x]; g[x]=tot;
}
int main(){
	while ( scanf("%d %d", &n, &m)==2 ){
		tot=0;
		memset( g, 0, sizeof( g ) );
		for ( int i=0; i<n; i++ ){ 
			int x;
			scanf("%d", &x);
			for ( int j=0; j<x; j++ ){
				int y;
				scanf("%d", &y);
				y--;
				insert( i, y );
			}
		}
		ans=0;
		hopcroft();
		printf("%d\n", ans);
	}
}
