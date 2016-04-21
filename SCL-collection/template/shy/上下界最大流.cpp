#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, S, T, DS, DT, a[1001], first[1501], next[100001], where[100001], v[100001], what[100001],
l, c[1501], dist[1501], len, pre[1501], way[1501], flow[1501], out[100001], tot, cnt, ans;

inline void makelist(int x, int y, int z, int q){
    where[++l] = y;
    v[l] = z;
    what[l] = q;
    next[l] = first[x];
    first[x] = l;
}

bool check(int S, int T){
    memset(dist, 0, sizeof(dist));
    c[1] = S; dist[S] = 1;
    for (int k = 1, l = 1; l <= k; l++)
    {
        int m = c[l];
        if (m == T)
        {
            len = dist[m] + 1;
            return(true);
        }
        for (int x = first[m]; x; x = next[x])
            if (v[x] && !dist[where[x]])
            {
                dist[where[x]] = dist[m] + 1; 
                c[++k] = where[x];
            }
    }
    return(false);
}

inline void dinic(int now, int S, int T){
    if (now == T)
    {
        int Minflow = 1 << 30;
        for (; now != S; now = pre[now]) Minflow = min(Minflow, v[way[now]]);
        ans += Minflow;
        for (now = T; now != S; now = pre[now]) 
        {
            v[way[now]] -= Minflow;
            v[way[now] ^ 1] += Minflow;
            if (!v[way[now]]) len = dist[now];
        }
        return;
    }
    for (int x = first[now]; x; x = next[x])
        if (v[x] && dist[where[x]] == dist[now] + 1)
        {
            pre[where[x]] = now;
            way[where[x]] = x;
            dinic(where[x], S, T);
            if (dist[now] >= len) return;
            len = dist[T] + 1;
        }
    dist[now] = -1;
}

int main(){
//    freopen("3229.in", "r", stdin);
//    freopen("3229.out", "w", stdout);
    for (;;)
    {
        if (scanf("%d%d", &n, &m) != 2) return 0;
        memset(first, 0, sizeof(first)); l = 1;
        memset(flow, 0, sizeof(flow));
        S = 0; T = n + m + 1; DS = T + 1; DT = DS + 1;
        for (int i = 1; i <= m; i++) 
        {
            scanf("%d", &a[i]);
            flow[S] -= a[i]; flow[i] += a[i];
            makelist(S, i, 1 << 30, 0); makelist(i, S, 0, 0);
        }
        tot = 0;
        for (int i = 1; i <= n; i++)
        {
            int C, D;
            scanf("%d%d", &C, &D);
            if (D) makelist(m + i, T, D, 0), makelist(T, m + i, 0, 0);
            for (int j = 1; j <= C; j++)
            {
                int idx, x, y;
                scanf("%d%d%d", &idx, &x, &y);
                idx++;
                flow[idx] -= x; flow[i + m] += x;
                out[++tot] = x;
                if (y != x) makelist(idx, i + m, y - x, tot), makelist(i + m, idx, 0, tot);
            }
        }
        cnt = 0;
        for (int i = S; i <= T; i++)
            if (flow[i] > 0) makelist(DS, i, flow[i], 0), makelist(i, DS, 0, 0), cnt += flow[i];
            else makelist(i, DT, abs(flow[i]), 0), makelist(DT, i, 0, 0);
        makelist(T, S, 1 << 30, 0); makelist(S, T, 0, 0);
        ans = 0;
        for (; check(DS, DT);) dinic(DS, DS, DT);
        if (ans != cnt) 
        {
            printf("-1\n\n");
            continue;
        }
        else
        {
            v[l] = v[l - 1] = 0;
            for (; check(S, T);) dinic(S, S, T);
            printf("%d\n", ans);
            for (int i = 3; i <= l; i += 2)
                if (what[i]) out[what[i]] += v[i];
            for (int i = 1; i <= tot; i++) printf("%d\n", out[i]);
            printf("\n");
        }
    }
}
        
