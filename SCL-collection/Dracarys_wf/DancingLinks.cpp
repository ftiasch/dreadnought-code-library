如果矩阵中所有的列均被删除, 找到一组合法解, 退出．
任意选择一个未被删除的列c, 
枚举一个未被删除的行r, 且Matrix[r][c] = 1, 将(r, c)加入Ans． 
枚举所有的列j, Matrix[r][j] = 1, 将第j列删除．
枚举所有的行i, Matrix[i][j] = 1, 将第i行删除．
            Algorithm_X(Dep + 1)

Procedure Algorithm_X(Dep)
        如果h^.right = h(即所有的列均被删除), 找到一组解, 退出．
        利用h和right指针找到一个c, 满足size[c]最小．
        如果size[c] = 0(当前列无法被覆盖), 无解, 退出．
Cover(c)
    for (i = c^.down; i != c; i ← i^.down)
       for (j = i^.right; j != i; j ← j^.right) Cover(j^.col)
       将i结点加入Ans, Algorithm_X(Dep + 1)
       for (j = i^.left; j != i; j ← j^.left) Recover(j^.col)
    	Recover(c)
Soduku问题可以转化一个Exact Cover Problem：16 * 16 * 16行, (i, j, k)表示(i, j)这个格子填上字母k．16 * 16 * 4列分别表示第i行中的字母k, 第i列中的字母k, 第i个子矩阵中的字母k, 以及(i, j)这个格子．对于每个集合(i, j, k), 它包含了4个元素：Line(i, k), Col(j, k), Sub(P[i][j], k), Grid(i, j), 其中P[i][j]表示(i, j)这个格子所属的子矩阵．本题转化为一个4096行, 1024列, 且1的个数为16384个的矩阵．下面介绍解决一般的Exact Cover Problem的Algorithm X．
N皇后问题：关键是构建Exact Cover问题的矩阵：N * N行对应了N * N个格子, 6N-2列对应了N行, N列, 2N-1条主对角线, 2N-1条副对角线．第i行共4个1, 分别对应(i, j)这个格子所处的行, 列, 主对角线和副对角线．直接对这个矩阵作Algorithm X是错误的, 虽然每行, 每列都恰好被覆盖一次, 但是对角线是最多覆盖一次, 它可以不被覆盖, 这与Exact Cover问题的定义是不同的．
有两种处理的方法：
1) 新增4N-2行, 每行只有一个1, 分别对应了2N-1条主对角线和2N-1条副对角线, 这样就可以保证某个对角线不被覆盖的时候, 可以使用新增行来覆盖．
2) 每次选择一个size[]值最小的列c进行覆盖, 而这一步, 我们忽略掉所有的对角线列, 只考虑c为行和列的情况．
事实证明, 第2)种方法的效果好很多, 因此这个问题可以使用Algorithm X轻松得到解决．

struct data
{
	int l,r,u,d,x,y;
};
data a[5101];
int sum[310];
void del(int x)
{
	a[a[x].l].r=a[x].r;
	a[a[x].r].l=a[x].l;
	for (int i=a[x].d;i!=x;i=a[i].d)
	for (int j=a[i].r;j!=i;j=a[j].r)
	{
		sum[a[j].y]--;
		a[a[j].u].d=a[j].d;
		a[a[j].d].u=a[j].u;
	}
}
void renew(int x)
{
	a[a[x].l].r=x;
	a[a[x].r].l=x;
	for (int i=a[x].u;i!=x;i=a[i].u)
	for (int j=a[i].l;j!=i;j=a[j].l)
	{
		sum[a[j].y]++;
		a[a[j].u].d=j;
		a[a[j].d].u=j;
	}
}
bool search()
{
	if (a[0].r==0)
	return(true);
	int k,min=20000000;
	for (int i=a[0].r;i!=0;i=a[i].r)
	if (sum[i]<min)
	min=sum[k=i];
	del(k);
	for (int i=a[k].d;i!=k;i=a[i].d)
	{
		for (int j=a[i].r;j!=i;j=a[j].r)
		del(a[j].y);
		if (search())
		return(true);
		for (int j=a[i].l;j!=i;j=a[j].l)
		renew(a[j].y);
	}
	renew(k);
	return(false);
}
