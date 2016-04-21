int isprime(long long n) {
	if(n<2) return 0;
	if(n<4) return 1;    
	if(strong_pseudo_primetest(n,2)==0) return 0;
	if(strong_pseudo_primetest(n,3)==0) return 0;
	if(n<1373653LL) return 1;
	if(strong_pseudo_primetest(n,5)==0) return 0;
	if(n<25326001LL) return 1;
	if(strong_pseudo_primetest(n,7)==0) return 0;
	if(n==3215031751LL) return 0;
	if(n<25000000000LL) return 1;
	if(strong_pseudo_primetest(n,11)==0) return 0;
	if(n<2152302898747LL) return 1;
	if(strong_pseudo_primetest(n,13)==0) return 0;
	if(n<3474749660383LL) return 1;
	if(strong_pseudo_primetest(n,17)==0) return 0;
	if(n<341550071728321LL) return 1;
	if(strong_pseudo_primetest(n,19)==0) return 0;
	if(strong_pseudo_primetest(n,23)==0) return 0;
	if(strong_pseudo_primetest(n,29)==0) return 0;
	if(strong_pseudo_primetest(n,31)==0) return 0;
	if(strong_pseudo_primetest(n,37)==0) return 0;
	return 1;
}
