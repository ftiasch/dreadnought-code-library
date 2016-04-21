#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

int test,n,SA[100001],c[100001],Rank[100001],tmp[100001],H[100001],f[100001];
char can[50001];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    scanf("%d",&test);                              
    for (test;test;test--)
    {
             scanf("%s\n",&can);
             n=strlen(can);
             memset(f,0,sizeof(f));
             for (int i=1;i<=n;i++) f[i]=int (can[i-1]);
             memset(c,0,sizeof(c));
             for (int i=1;i<=n;i++) c[f[i]]++;
             for (int i=1;i<=1000;i++) c[i]+=c[i-1];
             for (int i=n;i;i--) SA[c[f[i]]--]=i;
             Rank[SA[1]]=1;
             for (int i=2;i<=n;i++) 
                if (f[SA[i]]==f[SA[i-1]]) Rank[SA[i]]=Rank[SA[i-1]];
                else Rank[SA[i]]=Rank[SA[i-1]]+1;
             for (int L=1;L<=n;L+=L)
             {
                 if (Rank[SA[n]]==n) break;
                 memset(c,0,sizeof(c));
                 for (int i=1;i<=n;i++) c[Rank[L+i]]++;
                 for (int i=1;i<=n;i++) c[i]+=c[i-1];
                 for (int i=n;i;i--) tmp[c[Rank[L+i]]--]=i;
                 memset(c,0,sizeof(c));
                 for (int i=1;i<=n;i++) c[Rank[i]]++;
                 for (int i=1;i<=n;i++) c[i]+=c[i-1];
                 for (int i=n;i;i--) SA[c[Rank[tmp[i]]]--]=tmp[i];
                 tmp[SA[1]]=1;
                 for (int i=2;i<=n;i++)
                    if ((Rank[SA[i]]==Rank[SA[i-1]])&&(Rank[SA[i]+L]==Rank[SA[i-1]+L]))
                        tmp[SA[i]]=tmp[SA[i-1]];
                    else tmp[SA[i]]=tmp[SA[i-1]]+1;
                 for (int i=1;i<=n;i++) Rank[i]=tmp[i];
             }
    int p=0;
    for (int i=1;i<=n;i++)
    {
        int j=SA[Rank[i]-1];
        p-=1;
        if (p<0) p=0;
        while ((f[i+p]==f[j+p])) p++;
        H[i]=p;
    }
    int ans=0;
    for (int i=1;i<=n;i++)
        ans+=n-SA[i]+1-H[i];
    printf("%d\n",ans);
    }
}
