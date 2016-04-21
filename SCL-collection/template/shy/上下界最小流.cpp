#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

struct {
       int x, y, down, up;
} a[10001];
int out[100001], what[100001], cnt, S, T, DS, DT, l, ans, n, m, flow[101], first[201], next[100001], where[100001], v[100001], dist[201], c[201], pre[201], way[201], len;

int read(){
    char ch;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
    int cnt = 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) cnt = cnt * 10 + ch - '0';
    return(cnt);
}

inline void makelist(int x, int y, int z, int q){
    where[++l] = y;
    v[l] = z;
    what[l] = q;
    next[l] = first[x];
    first[x] = l;
}

inline void makemap(){       
    memset(first, 0, sizeof(first)); l = 1;
    S = 1, T = n, DS = 0, DT = n + 1; cnt = 0;
    for (int i = 1; i <= n; i++)
        if (flow[i] > 0) makelist(DS, i, flow[i], 0), makelist(i, DS, 0, 0), cnt += flow[i];
        else makelist(i, DT, abs(flow[i]), 0), makelist(DT, i, 0, 0);
    for (int i = 1; i <= m; i++) makelist(a[i].x, a[i].y, a[i].up - a[i].down, i),
                                 makelist(a[i].y, a[i].x, 0, i);
}

bool check(){
    memset(dist, 0, sizeof(dist));
    dist[DS] = 1; c[1] = DS;
    for (int k = 1, l = 1; l <= k; l++)
    {
        int m = c[l];
        if (m == DT) 
        {
           len = dist[m] + 1;
           return(true);
        }
        for (int x = first[m]; x; x = next[x])
            if (v[x] && !dist[where[x]]) dist[where[x]] = dist[m] + 1, c[++k] = where[x];
    }
    return(false);
}

inline void dinic(int now){
    if (now == DT)
    {
        int Minflow = 1 << 30;
        for (; now != DS; now = pre[now]) Minflow = min(Minflow, v[way[now]]);
        ans += Minflow;
        for (now = DT; now != DS; now = pre[now])
        {
            v[way[now]] -= Minflow;
            v[way[now] ^ 1] += Minflow;
            if (!v[way[now]]) len = dist[now];
        }
        return;
    }
    for (int x = first[now]; x; x = next[x])
        if (dist[where[x]] == dist[now] + 1 && v[x])
        {
            pre[where[x]] = now;
            way[where[x]] = x;
            dinic(where[x]);
            if (dist[now] >= len) return;
            len = dist[DT] + 1;
        }
    dist[now] = -1;
}

inline void network(){
    for (; check();) dinic(DS);
}

int main(){
   // freopen("176.in", "r", stdin);
   // freopen("176.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(flow, 0, sizeof(flow));    
    for (int i = 1; i <= m; i++) 
    {
        a[i].x = read(), a[i].y = read(), a[i].up = read();
        int status = read();
        if (status) a[i].down = a[i].up;
        else a[i].down = 0;
        flow[a[i].y] += a[i].down;
        flow[a[i].x] -= a[i].down;
    }
    makemap();
    ans = 0;
    network();
    makelist(T, S, 1 << 30, 0); makelist(S, T, 0, 0);
    network();
    if (ans != cnt) 
    {
        printf("Impossible\n");
        return 0;
    }
    printf("%d\n", v[l]);
    for (int i = 3; i <= l; i += 2)
        if (what[i]) out[what[i]] = v[i];
    for (int i = 1; i <= m; i++) 
    {
        printf("%d", a[i].down + out[i]);
        if (i != m) printf(" ");
        else printf("\n");
    }
}
    
        
    
