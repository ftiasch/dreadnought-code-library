#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int test, n, m, Q, first[501], a1[201], a2[201], flow[501], next[100001], where[100001], v[100001], len,
l, dist[501], c[501], up[201][201], down[201][201], S, T, DS, DT, ans, out[201][201], pre[501], way[501];

inline void makelist(int x, int y, int z){
    where[++l] = y;
    v[l] = z;
    next[l] = first[x];
    first[x] = l;
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
            if (v[x] && !dist[where[x]])
            {
               dist[where[x]] = dist[m] + 1;
               c[++k] = where[x];
            }
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
        if (v[x] && dist[now] + 1 == dist[where[x]])
        {
            pre[where[x]] = now;
            way[where[x]] = x;
            dinic(where[x]);
            if (dist[now] >= len) return;
            len = dist[DT] + 1;
        }
    dist[now] = -1;
}

int main(){
  //  freopen("2396.in", "r", stdin);
  //  freopen("2396.out", "w", stdout);
    scanf("%d", &test);
    for (int uu = 1; uu <= test; uu++)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &a1[i]);
        for (int i = 1; i <= m; i++) scanf("%d", &a2[i]);
        memset(up, 127, sizeof(up));
        memset(down, 0, sizeof(down));
        scanf("%d", &Q);
        for (int i = 1; i <= Q; i++)
        {
            int x, y, z;
            char str[2];
            scanf("%d%d%s%d", &x, &y, str, &z);
            int L1, L2, R1, R2;
            if (x == 0) L1 = 1, R1 = n;
            else L1 = R1 = x;
            if (y == 0) L2 = 1, R2 = m;
            else L2 = R2 = y;
            for (int j = L1; j <= R1; j++)
                for (int k = L2; k <= R2; k++)
                    if (str[0] == '>') down[j][k] = max(down[j][k], z + 1);
                    else if (str[0] == '<') up[j][k] = min(up[j][k], z - 1);
                    else down[j][k] = max(down[j][k], z), up[j][k] = min(up[j][k], z);
        }
        bool ok = true;
        for (int i = 1; i <= n && ok; i++)
            for (int j = 1; j <= m; j++)
                if (down[i][j] > up[i][j])
                {
                    ok = false;
                    break;
                }
        if (!ok) 
        {
           printf("IMPOSSIBLE\n");
           if (uu != test) printf("\n");
           continue;
        }
        memset(flow, 0, sizeof(flow));
        memset(first, 0, sizeof(first)); l = 1;
        S = 0; T = n + m + 1;
        for (int i = 1; i <= n; i++) flow[S] -= a1[i], flow[i] += a1[i];
        for (int i = 1; i <= m; i++) flow[i + n] -= a2[i], flow[T] += a2[i];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                flow[i] -= down[i][j]; flow[j + n] += down[i][j];
                if (down[i][j] != up[i][j]) makelist(i, j + n, up[i][j] - down[i][j]),  
                                            makelist(j + n, i, 0);
            }
        DS = T + 1; DT = DS + 1;
        int cnt = 0;
        for (int i = S; i <= T; i++)
            if (flow[i] > 0) makelist(DS, i, flow[i]), makelist(i, DS, 0), cnt += flow[i];
            else if (flow[i] < 0) makelist(i, DT, abs(flow[i])), makelist(DT, i, 0);
        makelist(T, S, 1 << 30); makelist(S, T, 0);
        ans = 0;
        for (; check();) dinic(DS);
        if (ans != cnt)
        {
            printf("IMPOSSIBLE\n");
            if (uu != test) printf("\n");
            continue;
        }
        for (int i = 1; i <= n; i++)
            for (int x = first[i]; x; x = next[x])
                if (where[x] >= n + 1 && where[x] <= n + m)
                   down[i][where[x] - n] += v[x ^ 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                printf("%d", down[i][j]);
                if (j != m) printf(" ");
                else printf("\n");
            }
        if (uu != test) printf("\n");
    }
}
