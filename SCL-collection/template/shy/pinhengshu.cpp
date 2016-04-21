#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

struct {
       int L,R,father,key,size;
} f[100001];
int root,n,Q;

inline void zig(int now){
    int x=f[now].father,y=f[x].father;
    if (y)
       if (f[y].L==x) f[y].L=now;
       else f[y].R=now;
    f[now].father=y;
    f[x].father=now;
    f[x].L=f[now].R;
    f[f[x].L].father=x;
    f[now].R=x;
    f[x].size=f[f[x].L].size+f[f[x].R].size+1;
    f[now].size=f[f[now].L].size+f[f[now].R].size+1;
}

inline void zag(int now){
    int x=f[now].father,y=f[x].father;
    if (y)
       if (f[y].L==x) f[y].L=now;
       else f[y].R=now;
    f[now].father=y;
    f[x].father=now;
    f[x].R=f[now].L;
    f[f[x].R].father=x;
    f[now].L=x;
    f[x].size=f[f[x].L].size+f[f[x].R].size+1;
    f[now].size=f[f[now].L].size+f[f[now].R].size+1;
}

inline void splay(int now){
    int x=f[now].father,y=f[x].father;
    while (x)
    {
          if (!y)
              if (f[x].L==now) zig(now);
              else zag(now);
          else if (f[y].L==x)
                  if (f[x].L==now) zig(x),zig(now);
                  else zag(now),zig(now);
               else if (f[x].L==now) zig(now),zag(now);
               else zag(x),zag(now);
          x=f[now].father;y=f[x].father;
    }
    root=now;
}
         
inline void insert(int now,int k){
    if (!root)
    {
       root=k;
       return;
    }
    if (f[k].key<=f[now].key) 
        if (!f[now].L) f[now].L=k,f[k].father=now,splay(k);
        else insert(f[now].L,k);
    else if (!f[now].R) f[now].R=k,f[k].father=now,splay(k);
         else insert(f[now].R,k);
}

inline void del(int now){
    splay(now);
    int LL=f[now].L,RR=f[now].R;
    f[now].L=f[now].R=f[now].key=f[now].father=f[now].size=0;
    f[LL].father=f[RR].father=0;
    if (!LL && !RR) root=0;
    else if (!LL) root=RR;
    else if (!RR) root=LL;
    else
    {
        root=RR;
        while (f[RR].L) RR=f[RR].L;
        f[RR].L=LL;
        f[LL].father=RR;
        splay(LL);
    }
}

int findkth(int now,int k){
    if (k==f[f[now].L].size+1) return(now);

int main(){
    scanf("%d",&n);
    root=0;
    for (int i=1;i<=n;i++)
        scanf("%d",&f[i].key),f[i].size=1,insert(root,i);
    scanf("%d",&Q);
    for (;Q--;)
    {
        int type;
        scanf("%d",&type);
        if (type==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            del(x);
            f[x].key=y;f[x].size=1;
            insert(root,x);
        }
        else
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",f[findkth(root,x)].key);
        }
    }
}
    
