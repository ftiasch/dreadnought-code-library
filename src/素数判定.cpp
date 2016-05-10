int strong_pseudo_primetest(long long n,int base) {
    long long n2=n-1,res;
    int s=0;
    while(n2%2==0) n2>>=1,s++;
    res=powmod(base,n2,n);
    if((res==1)||(res==n-1)) return 1;
    s--;
    while(s>=0) {
        res=mulmod(res,res,n);
        if(res==n-1) return 1;
        s--;
    }
    return 0; // n is not a strong pseudo prime
}
int isprime(long long n) {
	static LL testNum[]={2,3,5,7,11,13,17,19,23,29,31,37};
	static LL lim[]={4,0,1373653LL,25326001LL,25000000000LL,2152302898747LL, 3474749660383LL,341550071728321LL,0,0,0,0};
	if(n<2||n==3215031751LL) return 0;
	for(int i=0;i<12;++i){
		if(n<lim[i]) return 1;
		if(strong_pseudo_primetest(n,testNum[i])==0) return 0;
	}
	return 1;
}
