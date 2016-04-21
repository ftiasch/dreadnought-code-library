#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int nkd = 0, n, d, m;
template<typename T> struct vector
{
	T a[2];
	T & operator [] (int x) {return a[x];}
	const T & operator [] (int x) const {return a[x];}
};
struct kd
{
   kd * s[2];
   int i;
   vector<int> x;
   vector<int> find();
} kdpool[222222], *root;
vector<int> u, v, vec[111111];
long long dis(const vector<int> & a, const vector<int> & b)
{
   long long rtn = 0;
   for(int i = 0; i < d; i++) rtn += (long long)(a[i] - b[i]) * (a[i] - b[i]);
   return rtn;
}
void bize(int le, int ri, int index, int i)
{
	if(ri <= le) return;
   if(ri == le + 1)
   {
       if(vec[le][i] > vec[ri][i]) swap(vec[le], vec[ri]);
       return;
   }
   int l = le, r = ri, x = vec[le + rand() % (ri - le + 1)][i];
   for(;;)
   {
       while(vec[l][i] < x) l++;
       while(vec[r][i] > x) r--;
       if(l < r)
       {
           swap(vec[l], vec[r]);
           l++; r--;
       }
       if(l >= r) break;
   }
   int posi = le;
   while(posi <= ri and vec[posi][i] <= x) posi++;
   if(index <= posi - 1) bize(le, posi - 1, index, i);
   if(index >= posi) bize(posi, ri, index, i);
}
kd * build(int le, int ri, int i)
{
   if(le > ri) return 0;
   kd * p = &kdpool[++nkd];
   bize(le, ri, (le + ri) / 2, i);
   p->x = vec[(le + ri) / 2];
   p->i = i;
   if(le != ri)
   {
       p->s[0] = build(le, (le + ri) / 2 - 1, (i + 1) % d);
       p->s[1] = build((le + ri) / 2 + 1, ri, (i + 1) % d);
   }else p->s[0] = p->s[1] = 0;
   return p;
}
vector<int> kd::find()
{
   vector<int> rtn(x), tmp;
   double l; int go = v[i] > x[i];
   if(s[go])
   {
       tmp = s[go]->find();
       if(dis(tmp, v) < dis(rtn, v)) rtn = tmp;
   }
   l = sqrt(dis(rtn, v));
   if(v[i] - l < x[i] and x[i] < v[i] + l and s[go ^ 1])
   {
       tmp = s[go ^ 1]->find();
       if(dis(tmp, v) < dis(rtn, v)) rtn = tmp;
   }
   return rtn;
}
int main()
{
   scanf("%d%d", &n, &d);
   for(int i = 1; i <= n; i++)
   {
       for(int j = 0; j < d; j++)
           scanf("%d", &vec[i][j]);
   }
   root = build(1, n, 0);
   scanf("%d", &m);
   for(int i = 1; i <= m; i++)
   {
       for(int j = 0; j < d; j++)
           scanf("%d", &v[j]);
       u = root->find();
       for(int j = 0; j < d; j++)
       {
           printf("%d%c", u[j], j == d - 1?'\n':' ');
       }	
   }
   return 0;
}
