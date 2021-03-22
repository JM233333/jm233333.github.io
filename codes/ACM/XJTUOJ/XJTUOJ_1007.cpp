#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	//freopen("test.txt", "r", stdin);
	int T;
	int n, m;
	scanf("%d", &T);
	while (T --) {
		scanf("%d %d", &n, &m);
		if (m % (n - 1) == 0) {
			printf("CSFNB!\n");
		} else {
			double part = 1.0 * m / (n - 1);
			double res = ((n - 2) * ceil(part) + part) - m;
			printf("%.6f\n", res);
		}
	}
	return 0;
}
