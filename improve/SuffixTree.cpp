int pos;

struct Node {
	int l, r;
	
	Node *suf, *ch[C];
	
	Node (int l = -1, int r = INF) : l(l), r(r) {
		suf = 0;
		memset(ch, 0, sizeof(ch));
	}

	int len() {
		return min(r, pos + 1) - l;
	}
};

int top;

Node pool[N << 1];

Node *root, *nxtSuf, *cur;

int text[N];

int remCnt, curP, curLen;

void init() {
	top = 0, pos = -1, remCnt = 0, curP = 0, curLen = 0;
	nxtSuf = NULL;
	root = cur = new(pool + (top++)) Node(-1, -1);
}

void link(Node *u) {
	if (nxtSuf) {
		nxtSuf->suf = u;
	}
	nxtSuf = u;
}

bool walk(Node *u) {
	int len = u->len();
	if (curLen >= len) {
		curP += len;
		curLen -= len;
		cur = u;
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
			cur->ch[curE] = new(pool + (top++)) Node(pos);
			link(cur);
		} else {
			Node *nxt = cur->ch[curE];
			if (walk(nxt)) {
				continue;
			}
			if (text[nxt->l + curLen] == c) {
				++curLen;
				link(cur);
				break;
			}
			Node *split = new(pool + (top++)) Node(nxt->l, nxt->l + curLen);
			cur->ch[curE] = split;
			split->ch[c] = new(pool + (top++)) Node(pos);	
			nxt->l += curLen;
			split->ch[text[nxt->l]] = nxt;
			link(split);
		}
		--remCnt;
		if (cur == root && curLen > 0) {
			--curLen;
			curP = pos - remCnt + 1;
		} else {
			cur = cur->suf ? cur->suf : root;
		}
	}
}

void finish() {
	nxtSuf = NULL;
	for (int i = 0; i < top; ++i) {
		if (pool[i].r == INF) {
			link(pool + i);
		}
	}
	while (remCnt > 0) {
		if (curLen) {
			int curE = text[curP];
			Node *nxt = cur->ch[curE];
			if (walk(nxt)) {
				continue;
			}
			Node *split = new(pool + (top++)) Node(nxt->l, nxt->l + curLen);
			cur->ch[curE] = split;
			nxt->l += curLen;
			split->ch[text[nxt->l]] = nxt;
			link(split);
		} else {
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
	if (nxtSuf != root) {
		link(root);
	}
}

int buf[N];

struct Walker {
	Node *cur, *root;
	int curP, curLen, pos, totLen;

	Walker(Node* root) : root(root) {
		cur = root;
		curP = -1;
		curLen = 0;
		totLen = 0;
		pos = -1;
	}

	void descend() {
		while (curLen > 0) {
			Node *nxt = cur->ch[buf[curP]];
			int len = nxt->len();
			if (curLen >= len) {
				curP += len;
				curLen -= len;
				cur = nxt;
			} else {
				break;
			}
		}
	}

	void walk(int c) {
		buf[++pos] = c;
		while (curLen) {
			Node *nxt = cur->ch[buf[curP]];
			if (nxt->l + curLen <= ::pos && text[nxt->l + curLen] == c) {
				++totLen;
				++curLen;
				break;
			} else {
				--totLen;
				if (cur == root && curLen > 0) {
					--curLen;
					curP = pos - curLen;
				} else {
					cur = cur->suf;
				}
				descend();
			}
		}
		if (curLen == 0) {
			curP = pos;
			int curE = buf[curP];
			while (cur && !cur->ch[curE]) {
				--totLen;
				cur = cur->suf;
			}
			if (cur) {
				++totLen;
				curLen = 1;
			} else {
				cur = root;
				totLen = 0;
			}
		}
		descend();
	}
};

