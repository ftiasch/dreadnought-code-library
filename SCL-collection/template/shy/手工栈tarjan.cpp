#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, first[10001], father[10001], dfn[10001], low[10001], c[10001], pos[10001], todo[10001], 
cnt, len, next[2000001], where[2000001], l, kuai, Max, color[10001], number;
bool b[10001];

int read(){
    char ch;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
    int cnt = 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) cnt = cnt * 10 + ch - '0';
    return(cnt);
}

inline void makelist(int x, int y){
    where[++l] = y;
    next[l] = first[x];
    first[x] = l;
}

inline void tarjan(int S){
    int now = S; todo[now] = first[now];
    for (;;)
    {
        if (!now) return;
        if (first[now] == todo[now])
        {
            b[now] = true;
            dfn[now] = low[now] = ++cnt;   
            c[++len] = now; pos[now] = len;
        }
        int x = todo[now];
        if (!x) 
        {
            if (father[now])
                low[father[now]] = min(low[father[now]], low[now]);
            int delta = -1;
            if (father[now]) ++delta;
            for (int x = first[now]; x; x = next[x])
                if (father[where[x]] == now) 
                    if (low[where[x]] >= dfn[now]) ++delta;
            Max = max(Max, delta);
            if (low[now] == dfn[now])
            {
               ++number;
               for (int i = pos[now]; i <= len; i++) color[c[i]] = number;
               len = pos[now] - 1;
            }
            now = father[now];
            continue;
        }
        todo[now] = next[todo[now]];
        if (father[now] != where[x]) 
            if (!b[where[x]])
            {
                father[where[x]] = now;
                now = where[x];
                todo[now] = first[now];
                continue;
            }
            else if (!color[where[x]]) low[now] = min(low[now], dfn[where[x]]);
    }
}
                
int main(){
   // freopen("2117.in", "r", stdin);
   // freopen("2117.out", "w", stdout);
    for (;;)
    {
        n = read(); m = read();
        if (!n && !m) return 0;
        memset(first, 0, sizeof(first));
        l = 0;
        for (int i = 1; i <= m; i++)
        {
            int x = read() + 1, y = read() + 1;
            makelist(x, y);
            makelist(y, x);
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(color, 0, sizeof(color));
        memset(b, false, sizeof(b));
        memset(father, 0, sizeof(father));
        cnt = 0; len = 0;
        Max = - (1 << 30); 
        kuai = 0; number = 0;
        for (int i = 1; i <= n; i++)
            if (!b[i]) tarjan(i), ++kuai;
        printf("%d\n", kuai + Max);
    }
}
