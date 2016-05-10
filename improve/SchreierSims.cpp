struct Permutation{
	vector<int> P;Permutation(){} Permutation(int n){ P.resize(n); }
	Permutation inv()const{
		Permutation ret(P.size());
		for(int i = 0; i < int(P.size()); ++i) ret.P[P[i]] = i;
		return ret;
	}
	int &operator [](const int &dn){ return P[dn]; }
	void resize(const size_t &sz){ P.resize(sz); }
	size_t size()const{ return P.size(); }
	const int &operator [](const int &dn)const{ return P[dn]; }
};
Permutation operator *(const Permutation &a, const Permutation &b){
	Permutation ret(a.size());
	for(int i = 0; i < (int)a.size(); ++i) ret[i] = b[a[i]];
	return ret;
}
typedef vector<Permutation> Bucket;
typedef vector<int> Table; typedef pair<int,int> pii;
int n, m;
vector<Bucket> buckets, bucketsInv; vector<Table> lookupTable;
int fastFilter(const Permutation &g, bool addToGroup = true){
	int n = buckets.size();
	Permutation p;
	for(int i = 0; i < n; ++i){
		int res = lookupTable[i][p[i]];
		if(res == -1){
			if(addToGroup){
				buckets[i].push_back(p); bucketsInv[i].push_back(p.inv());
				lookupTable[i][p[i]] = (int)buckets[i].size() - 1;
			}
			return i;
		}
		p = p * bucketsInv[i][res]; swap(i1,i2);
	}
	return -1;
}
long long calcTotalSize(){
	long long ret = 1;
	for(int i = 0; i < n; ++i) ret *= buckets[i].size(); 
	return ret;
}
bool inGroup(const Permutation &g){ return fastFilter(g, false) == -1; }
void solve(const Bucket &gen,int _n){// m perm[0..n - 1]s
	n = _n, m = gen.size();
	{//clear all
		vector<Bucket> _buckets(n); swap(buckets, _buckets);
		vector<Bucket> _bucketsInv(n); swap(bucketsInv, _bucketsInv);
		vector<Table> _lookupTable(n); swap(lookupTable, _lookupTable);
	}
	for(int i = 0; i < n; ++i){
		lookupTable[i].resize(n);
		fill(lookupTable[i].begin(), lookupTable[i].end(), -1);
	}
	Permutation id(n);
	for(int i = 0; i < n; ++i) id[i] = i;
	for(int i = 0; i < n; ++i){
		buckets[i].push_back(id); bucketsInv[i].push_back(id);
		lookupTable[i][i] = 0;
	}
	for(int i = 0; i < m; ++i) fastFilter(gen[i]);
	queue<pair<point,point> > toUpdate;
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j)
			for(int k = 0; k < (int)buckets[i].size(); ++k)
				for(int l = 0; l < (int)buckets[j].size(); ++l)
					toUpdate.push(make_pair(pii(i,k), pii(j,l)));
	while(!toUpdate.empty()){
		pii a = toUpdate.front().first, b = toUpdate.front().second;
		toUpdate.pop();
		int res=fastFilter(buckets[a.first][a.second]*buckets[b.first][b.second]);
		if(res==-1) continue;
		pii newPair(res, (int)buckets[res].size() - 1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < (int)buckets[i].size(); ++j){
				if(i <= res) toUpdate.push(make_pair(pii(i, j), newPair));
				if(res <= i) toUpdate.push(make_pair(newPair, pii(i, j)));
			}
	}
}
