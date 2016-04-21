#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

int a[100001][27],fail[100001],last[100001],c[100001],l,father[100001],type[100001];
char can[1001];

inline void maketrie(){
    memset(a,0,sizeof(a));
    memset(type,0,sizeof(type));
    memset(last,0,sizeof(last));
    int n=strlen(can),now=0;
    l=0;
    for (int i=0;i<n;i++) 
    {
        if (!a[now][can[i]-'A']) a[now][can[i]-'A']=++l,type[l]=can[i]-'A',father[l]=now;
        now=a[now][can[i]-'A'];
    }
    last[now]=1;
}

inline void makefail(){
    memset(fail,255,sizeof(fail));
    fail[0]=0;
    int k=0;
    for (int i=0;i<=25;i++) 
       if (a[0][i]) fail[a[0][i]]=0,c[++k]=a[0][i];
    for (int l=1;l<=k;l++)
    {
        int m=c[l];
        if (fail[m]==-1)
        {
           int p=father[m];
           while (p && !a[fail[p]][type[m]]) p=fail[p];
           fail[m]=a[fail[p]][type[m]];
           last[m]+=last[fail[m]];
        }
        for (int i=0;i<=25;i++) 
            if (a[m][i]) c[++k]=a[m][i];
    }
}
         
int main(){ 
    scanf("%s",can);
    maketrie();
    makefail();     
}
