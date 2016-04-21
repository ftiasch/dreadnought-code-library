int ansn;
LL ans[1000];
LL mod_mul(LL x,LL y,LL n){
	long long d = (long long)((long double)x*y/n);
	d=x*y-n*d;
	while (d < 0) d += n;
	while (d >= n) d -= n;
	return d;
}
LL myrand(){
	LL a=rand();
	a*=rand();
	return abs(a);
}
LL mod_exp(LL a,LL x,LL n){
	LL ret=1;
	while(x){
		if(x&1) ret=mod_mul(ret,a,n);
		a=mod_mul(a,a,n);
		x>>=1;
	}
	return ret;
}
LL gcd(LL x,LL y){
	LL q;
	while(1){
		if(!y) return abs(x);
		q=x,x=y,y=q%y;
	}
}
bool Rabin_Miller(LL n){
	LL k=0,i,j,m,a;
	if(n<2) return 0;
	if(n==2) return 1;
	if(!(n&1)) return 0;
	m=n-1;
	while(!(m&1)) m>>=1,k++;
	for(i=0;i<20;i++){
		a=myrand()%(n-2)+2;
		a=mod_exp(a,m,n);
		if(a==1) continue;
		for(j=0;j<k;j++){
			if(a==n-1)
			break;
			a=mod_mul(a,a,n);
		}
		if(j<k) continue;
		return 0;
	}
	return 1;
}
LL func(LL x,LL n){
	return (mod_mul(x,x,n)+1)%n;
}
LL Pollard(LL n){
	LL i,x,y,p;
	if(Rabin_Miller(n)) return n;
	if(!(n&1)) return 2;
	for(i=1;i<20;i++){
		x=i;
		y=func(x,n);
		p=gcd(y-x,n);
		while(p==1){
			x=func(x,n);
			y=func(func(y,n),n);
			p=gcd((y-x+n)%n,n)%n;
		}
		if(p==0||p==n)
		continue;
		return p;
	}
}
void factor(LL n){
	LL x;
	x=Pollard(n);
	if(x==n){
		ans[ansn++]=x;
		return;
	}
	factor(x);
	factor(n/x);
}
void output(){
	int i,j;
	LL tmp;
	for(i=0;i<ansn;i++)
	for(j=i+1;j<ansn;j++)
	if(ans[i]>ans[j]){
		tmp=ans[i];
		ans[i]=ans[j];
		ans[j]=tmp;
	}
	for (i = 0; i < ansn; i += j) {
		for (j = 0; i + j < ansn && ans[i] == ans[i + j]; j++);
		if (i) cout << " *";
		cout << " " << ans[i];
		if (j > 1) cout << "^" << j;
	}
	cout << endl;
}
int main(){
	LL n;
	srand((unsigned)time(NULL));
	int tt;
	scanf("%d", &tt);
	while(tt--){
		cin >> n;
		if(n==1){
			cout<<"1 = 1"<<endl;
			continue;
		}
		if(n<0)
		break;
		ansn=0;
		factor(n);
		cout << n << " =";
		output();
	}
	return 0;
}

