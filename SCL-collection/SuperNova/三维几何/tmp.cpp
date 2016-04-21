/*
   a*x^2+b*x+c==0 (mod P)
   求 0..P-1 的根
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define sqr(x) ((x)*(x))
int pDiv2,P,a,b,c,Pb,d;
inline int calc(int x,int Time)
{
	if (!Time) return 1;
	int tmp=calc(x,Time/2);
	tmp=(long long)tmp*tmp%P;
	if (Time&1) tmp=(long long)tmp*x%P;
	return tmp;
}
inline int rev(int x)
{
	if (!x) return 0;
	return calc(x,P-2);
}
inline void Compute()
{
	while (1)
	{
		b=rand()%(P-2)+2;
		if (calc(b,pDiv2)+1==P) return;
	}
}
int main()
{
	srand(time(0)^312314);
	int T;
	for (scanf("%d",&T);T;--T)
	{
		scanf("%d%d%d%d",&a,&b,&c,&P);
		if (P==2)
		{
			int cnt=0;
			for (int i=0;i<2;++i)
				if ((a*i*i+b*i+c)%P==0) ++cnt;
			printf("%d",cnt);
			for (int i=0;i<2;++i)
				if ((a*i*i+b*i+c)%P==0) printf(" %d",i);
			puts("");
		}else
		{
			int delta=(long long)b*rev(a)*rev(2)%P;
			a=(long long)c*rev(a)%P-sqr( (long long)delta )%P;
			a%=P;a+=P;a%=P;
			a=P-a;a%=P;
			pDiv2=P/2;
			if (calc(a,pDiv2)+1==P) puts("0");
			else
			{
				int t=0,h=pDiv2;
				while (!(h%2)) ++t,h/=2;
				int root=calc(a,h/2);
				if (t>0)
				{
					Compute();
					Pb=calc(b,h);
				}
				for (int i=1;i<=t;++i)
				{
					d=(long long)root*root*a%P;
					for (int j=1;j<=t-i;++j)
						d=(long long)d*d%P;
					if (d+1==P)
						root=(long long)root*Pb%P;
					Pb=(long long)Pb*Pb%P;
				}
				root=(long long)a*root%P;
				int root1=P-root;
				root-=delta;
				root%=P;
				if (root<0) root+=P;
				root1-=delta;
				root1%=P;
				if (root1<0) root1+=P;
				if (root>root1)
				{
					t=root;root=root1;root1=t;
				}
				if (root==root1) printf("1 %d\n",root);
				else printf("2 %d %d\n",root,root1);
			}
		}
	}
	return 0;
}

