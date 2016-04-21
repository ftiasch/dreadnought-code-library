std::string find(std::string s) {
	int i,j,k,l,N=s.length(); s+=s;
	for(i=0,j=1;j<N;){
		for(k=0;k<N&&s[i+k]==s[j+k];k++);
		if(k>=N) break;
		if(s[i+k]<s[j+k]) j+=k+1;
		else l=i+k,i=j,j=max(l,j)+1;
	}
	return s.substr(i,N);
}
