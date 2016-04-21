int ansn; LL ans[1000];
LL func(LL x,LL n){ return(mod_mul(x,x,n)+1)%n; }
LL Pollard(LL n){
	LL i,x,y,p;
	if(Rabin_Miller(n)) return n;
	if(!(n&1)) return 2;
	for(i=1;i<20;i++){
		x=i; y=func(x,n); p=gcd(y-x,n);
		while(p==1) {x=func(x,n); y=func(func(y,n),n); p=gcd((y-x+n)%n,n)%n;}
		if(p==0||p==n) continue;
		return p;
	}
}
void factor(LL n){
	LL x;
	x=Pollard(n);
	if(x==n){ ans[ansn++]=x; return; }
	factor(x), factor(n/x);
}