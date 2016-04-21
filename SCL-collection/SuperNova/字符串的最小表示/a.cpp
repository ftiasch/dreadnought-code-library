#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int minCycle(char *a)
{
	int n = strlen(a);
	for(int i = 0; i < n; ++ i) {
		a[i + n] = a[i];
	}
	a[n + n] = 0;
	int i = 0, j = 1, k = 0;
	do {
		for(k = 0; a[i + k] == a[j + k]; ++ k);
		if (a[i + k] > a[j + k]) i = i + k + 1;
		else j = j + k + 1;
		j += i == j;
		if (i > j) swap(i, j);
	} while(j < n);
	return i;
}

char s[10000];

int main()
{
	gets(s);
	int n = strlen(s);
	int k = minCycle(s);
	for(int i = 0; i < n; ++ i) {
		putchar(s[(i + k) % n]);
	}
	cout << endl;
	return 0;
}

