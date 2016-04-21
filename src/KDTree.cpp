#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
// 带插入版本 , 没有写内存回收 , 空间复杂度 $n \log n$ , 如果不需要插入可以大大简化
// N 为最大点数, D 为每个点的最大维度, d 为实际维度
// 以查找最近点为例 ret 为当前最近点的距离的平方 , 用来剪枝 , 查询 k 近或 k 远的方法类似
// 使用时注意先 initNull
const long long INF = (int)1e9 + 10;
const int N = 2000000 + 10;
const int D = 5;
const double SCALE = 0.75;
struct Point { int x[D]; } buf[N];
int d;
struct Node {
	int depth, size;
	Node *ch[2], *p;
	Point val, maxv, minv;
	void set(Node *t, int d) { ch[d] = t; t->p = this; }
	bool dir() { return this == p->ch[1]; }
	bool balanced() {
		return (double)max(ch[0]->size, ch[1]->size) <= (double)size * SCALE;
	}
	void update() {
		size = ch[0]->size + ch[1]->size + 1;
		for(int i = 0; i < d; ++ i) {
			maxv.x[i] = max(val.x[i], max(ch[0]->maxv.x[i], ch[1]->maxv.x[i]));
			minv.x[i] = min(val.x[i], min(ch[0]->minv.x[i], ch[1]->minv.x[i]));
		}
	}
} nodePool[N], *totNode, *null;
Node* newNode(Point p, int depth) {
	Node *t = totNode ++;
	t->ch[0] = t->ch[1] = t->p = null;
	t->depth = depth;
	t->val = t->maxv = t->minv = p;
	t->size = 1;
	return t;
}
long long ret;
int ctr;
int cmp(const Point &a, const Point &b) { return a.x[ctr] < b.x[ctr]; }
struct KDTree {
	Node *root;
	KDTree() { root = null; } 
	KDTree(Point *a, int n) {
		root = build(a, 0, n - 1, 0);
	}
	Node *build(Point *a, int l, int r, int depth) {
		if (l > r) return null;
		ctr = depth;
		sort(a + l, a + r + 1, cmp);
		int mid = (l + r) >> 1;
		Node *t = newNode(a[mid], depth);
		t->set(build(a, l, mid - 1, (depth + 1) % d), 0);
		t->set(build(a, mid + 1, r, (depth + 1) % d), 1);
		t->update();
		return t;
	}
	void tranverse(Node *t, Point *vec, int &tot) {
		if (t == null) return;
		vec[tot ++] = t->val;
		tranverse(t->ch[0], vec, tot);
		tranverse(t->ch[1], vec, tot);
	}
	void rebuild(Node *t) {
		Node *p = t->p;
		int tot = 0;
		tranverse(t, buf, tot);
		Node *u = build(buf, 0, tot - 1, t->depth);
		p->set(u, t->dir());
		for( ; p != null; p = p->p) p->update();
		if (t == root) root = u;
	}
	void insert(Point p) {
		if (root == null) { root = newNode(p, 0); return; }
		Node *cur = root, *last = null;
		int dir = 0;
		for( ; cur != null; ) {
			last = cur;
			dir = (p.x[cur->depth] > cur->val.x[cur->depth]);
			cur = cur->ch[dir];
		}
		Node *t = newNode(p, (last->depth + 1) % d), *bad = null;
		last->set(t, dir);
		for( ; t != null; t = t->p) {
			t->update();
			if (!t->balanced()) bad = t;
		}
		if (bad != null) rebuild(bad);
	}
	long long calcEval(Point u, Node *t, int d) {
		long long l = t->minv.x[d], r = t->maxv.x[d], x = u.x[d];
		if (x >= l && x <= r) return 0LL;
		long long ret = min(abs(x - l), abs(x - r));
		return ret * ret;
	}
	void updateAns(Point u, Point p) {
		// 在这里更新答案 
	}
	void query(Node *t, Point p) {
		if (t == null) return;
		updateAns(t->val, p);
		long long evalLeft = calcEval(p, t->ch[0], t->depth);
		long long evalRight = calcEval(p, t->ch[1], t->depth);
		if (evalLeft <= evalRight) {
			query(t->ch[0], p);
			if (ret > evalRight) query(t->ch[1], p);
		} else {
			query(t->ch[1], p);
			if (ret > evalLeft) query(t->ch[0], p);
		}
	}
	void query(Point p) {
		query(root, p);
	}
};
void initNull() {
	totNode = nodePool;
	null = totNode ++;
	null->size = 0;
	for(int i = 0; i < d; ++ i) {
		null->maxv.x[i] = -INF;
		null->minv.x[i] = INF;
	}
}
