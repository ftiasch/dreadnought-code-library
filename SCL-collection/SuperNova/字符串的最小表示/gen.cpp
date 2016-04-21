#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<cstdio>

using namespace std;

int main()
{
	srand(time(0));
	int n = rand() % 1000 + 1;
	for(int i = 0; i < n; ++ i) {
		putchar(rand() % 2 + 'a');
	}
	putchar('\n');
	return 0;
}
