#include<string>
#include<iostream>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int n = s.length();
	string ret = s;
	s = s + s;
	for(int i = 0; i < n; ++ i) {
		string tmp = s.substr(i, n);
		if (tmp < ret) ret = tmp;
	}
	cout << ret << endl;
	return 0;
}
