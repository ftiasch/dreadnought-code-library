//Int g[][] 为图的邻接矩阵 标号由 1 至 n
//MC(V) 表示点集 V 的最大团 令 Si={vi, vi+1, ..., vn}, mc[i] 表示 MC(Si)
// 倒着算 mc[i], 那么显然 MC(V)=mc[1] 此外有 mc[i]=mc[i+1] or mc[i]=mc[i+1]+1
void dfs(int size){
	if (len[size]==0) {
		if (size>ans) ans=size, found=true; return;
	} for (int k=0,i,j; k<len[size] && !found; ++k) {
		if (size+len[size]-k<=ans) break;
		i=list[size][k]; if (size+mc[i]<=ans) break;
		for (j=k+1, len[size+1]=0; j<len[size]; ++j)
		if (g[i][list[size][j]]) list[size+1][len[size+1]++]=list[size][j];
		dfs(size+1);
}}
void work(){
	mc[n]=ans=1;
	for (int i=n-1; i; --i) {
		found=false; len[1]=0;
		for (int j=i+1; j<=n; ++j) if (g[i][j]) list[1][len[1]++]=j;
		dfs(1); mc[i]=ans;
}}
