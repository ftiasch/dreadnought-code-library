#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

struct {
       int pos,tot;
} w[2000001];

const int inf=120234234;
int n,m,l,len,first[5001],c[2000001],dist[5001],where[200001],next[200001],v[200001],f[5001],lenn[5001];
bool b[5001];

inline void makelist(int x,int y,int z){
    where[++l]=y;
    v[l]=z;
    next[l]=first[x];
    first[x]=l;
}

inline void spfa(){
    memset(b,false,sizeof(false));
    memset(f,127,sizeof(f));
    f[n]=0;
    c[1]=n;
    for (int k=1,l=1;l<=k;l++)
     {
             int m=c[l];
             b[m]=false;
             for (int x=first[m];x;x=next[x])
                 if (f[m]+v[x]<f[where[x]])
                 {
                     f[where[x]]=f[m]+v[x];
                     if (!b[where[x]])
                     {
                         b[where[x]]=true;
                         c[++k]=where[x];
                     }
                 }
     }
}

inline void insect(int re,int uu){
    w[++len].pos=re;
    w[len].tot=uu;
    int now=len;
    while (now!=1)
      if (w[now].tot+f[w[now].pos]<w[now>>1].tot+f[w[now>>1].pos])
        {
           int k=w[now].tot;
           w[now].tot=w[now>>1].tot;
           w[now>>1].tot=k;
           k=w[now].pos;
           w[now].pos=w[now>>1].pos;
           w[now>>1].pos=k;
           now=now>>1;
        }
      else break;
}

inline void delete1(){
    w[1].pos=w[len].pos;
    w[1].tot=w[len].tot;
    w[len].pos=inf;
    w[len].tot=inf;
    len--;
    int now=1;
    while ((now<<1)<=len)
      if ((now<<1)==len)
       if (w[now<<1].tot+f[w[now<<1].pos]<w[now].tot+f[w[now].pos])
      {
           int k=w[now].tot;
           w[now].tot=w[now<<1].tot;
           w[now<<1].tot=k;
           k=w[now].pos;
           w[now].pos=w[now<<1].pos;
           w[now<<1].pos=k;
           now=now<<1;
      }
      else break; 
      else
      if ((w[now<<1].tot+f[w[now<<1].pos]<w[(now<<1)+1].tot+f[w[(now<<1)+1].pos]))
      if (w[now<<1].tot+f[w[now<<1].pos]<w[now].tot+f[w[now].pos])
      {
           int k=w[now].tot;
           w[now].tot=w[now<<1].tot;
           w[now<<1].tot=k;
           k=w[now].pos;
           w[now].pos=w[now<<1].pos;
           w[now<<1].pos=k;
           now=now<<1;
      }
      else break;
      else 
      if (w[(now<<1)+1].tot+f[w[(now<<1)+1].pos]<w[now].tot+f[w[now].pos])
      {
           int k=w[now].tot;
           w[now].tot=w[(now<<1)+1].tot;
           w[(now<<1)+1].tot=k;
           k=w[now].pos;
           w[now].pos=w[(now<<1)+1].pos;
           w[(now<<1)+1].pos=k;
           now=(now<<1)+1;
      }
      else break;
}

inline void spfa_ans(){
    memset(dist,127,sizeof(dist));
    memset(lenn,0,sizeof(lenn));
    memset(w,127,sizeof(w));
    c[1]=1;
    len=1;
    w[1].pos=1;
    w[1].tot=0;
    for (int k=1,l=1;l<=k;)
      {
             int m=w[1].pos,flow=w[1].tot;
             delete1();
             dist[m]=inf;
             lenn[m]++;
             if (lenn[m]>1000) 
             {
                printf("%d\n",-1);
                return;
             }
             if ((m==n)&&(lenn[m]==2)) 
              {
                    printf("%d\n",flow);
                    return;
              }
             for (int x=first[m];x;x=next[x])
                    {
                       dist[where[x]]=flow+v[x];
                       insect(where[x],dist[where[x]]);
                    }
      }
}
                    
                 
             
             
    
int main(){
    scanf("%d%d",&n,&m);
    l=0;
    for (int i=1;i<=m;i++)
      {
             int x,y,z;
             scanf("%d%d%d",&x,&y,&z);
             makelist(x,y,z);
             makelist(y,x,z);
      }
    spfa();
    spfa_ans();
}
