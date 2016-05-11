int pos, text[N];
struct Node {
	int l, r;
	Node *suf, *ch[C];
	int dgr;
	Node *fa;
	Node (int l = -1, int r = INF) : l(l), r(r) {
		suf = fa = NULL;
		memset(ch, 0, sizeof(ch));
		dgr = 0;
	}
	Node* addEdge(Node *t) {
		int c = text[t->l];
		dgr += !ch[c];
		ch[c] = t;
		t->fa = this;
		return t;
	}
	int len() {
		return min(r, pos + 1) - l;
	}
};

int top;
Node pool[N << 1], *root, *nxtSuf, *cur;
int remCnt, curP, curLen;
long long size;
queue<Node*> leaves;
void init() {
	top = 0, pos = -1;
	remCnt = 0, curP = 0, curLen = 0;
	nxtSuf = NULL;
	root = cur = new(pool + (top++)) Node(-1, -1);
	size = 0;
	while (leaves.size()) leaves.pop();
}
void link(Node *u) {
	if (nxtSuf) nxtSuf->suf = u;
	nxtSuf = u;
}
bool walk(Node *u) {
	int len = u->len();
	if (curLen >= len) {
		curP += len, curLen -= len, cur = u;
		return true;
	}
	return false;
}
void extend(int c) {
	text[++pos] = c;
	nxtSuf = NULL;
	++remCnt;
	while (remCnt) {
		curP = curLen ? curP : pos;
		int curE = text[curP];
		if (!cur->ch[curE]) {
			leaves.push(cur->addEdge(new(pool + (top++)) Node(pos)));
			link(cur);
		} else {
			Node *nxt = cur->ch[curE];
			if (walk(nxt)) continue;
			if (text[nxt->l + curLen] == c) {
				++curLen;
				link(cur);
				break;
			}
			Node *split = new(pool + (top++)) Node(nxt->l, nxt->l + curLen);
			cur->addEdge(split);
			leaves.push(split->addEdge(new(pool + (top++)) Node(pos)));
			nxt->l += curLen;
			split->addEdge(nxt);
			link(split);
		}
		--remCnt;
		if (cur == root && curLen > 0) {
			curP = pos - (--curLen);
		} else {
			cur = cur->suf ? cur->suf : root;
		}
	}
	size += leaves.size();
}
void finish() {
	nxtSuf = NULL;
	for (int i = 0; i < top; ++i) if (pool[i].r == INF) link(pool + i);
	while (remCnt > 0) {
		if (curLen) {
			int curE = text[curP];
			Node *nxt = cur->ch[curE];
			if (walk(nxt)) continue;
			Node *split = new(pool + (top++)) Node(nxt->l, nxt->l + curLen);
			leaves.push(cur->addEdge(split));
			nxt->l += curLen;
			split->addEdge(nxt);
			link(split);
		} else {
			leaves.push(cur);
			link(cur);
		}
		--remCnt;
		if (cur == root && curLen > 0) {
			--curLen;
			curP = pos - remCnt + 1;
		} else {
			cur = cur->suf ? cur->suf : root;
		}
	}
	if (nxtSuf != root) link(root);
}
void eraseUp(Node *&u) {
	size -= u->len();
	int ch = text[u->l];
	u = u->fa;
	u->ch[ch] = NULL;
	--(u->dgr);
}
void erase() {
	Node *u = leaves.front();
	leaves.pop();
	while (u->dgr == 0 && u != cur) eraseUp(u);
	if (u == cur) {
		if (cur->dgr == 0 && curLen == 0) {
			int len = u->len();
			curLen = len;
			curP = pos - len + 1;
			cur = cur->fa;
			eraseUp(u);
		}
		if (curLen) {
			int curE = text[curP];
			if (!cur->ch[curE]) {
				Node *leaf = new(pool + (top++)) Node(pos - curLen + 1);
				leaves.push(cur->addEdge(leaf));
				size += leaf->len();
				--remCnt;
				if (cur == root && curLen > 0) {
					curP = pos - (--curLen) + 1;
				} else {
					cur = cur->suf ? cur->suf : root;
				}
				while (curLen && walk(cur->ch[text[curP]])) continue; 
			}
		}
	}
}
int n;
char s[N], buf[N];
int ord[N], stop, sord[N << 1];
void dfs(Node *u) {
	sord[u - pool] = stop++;
	for (int i = 0; i < C; ++i) {
		if (u->ch[i]) {
			dfs(u->ch[i]);
		}
	}
}
void getOrd() {
	init();
	for (int i = 0; i < n; ++i) extend(s[i] - 'a');
	finish();
	stop = 0;
	dfs(root);
	int i = 0;
	while (leaves.size()) {
		ord[i++] = sord[leaves.front() - pool];
		leaves.pop();
	}
}
