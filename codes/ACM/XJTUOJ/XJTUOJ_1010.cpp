#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

bool check(int x, int y);
bool is_legal(int x, int y);

const int MAX = 55;
char mount[MAX][MAX], flower[MAX][MAX];
int N, M, n, m;

int main() {
	//freopen("test.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T --) {
		// 输入
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i ++) {
			scanf("%s", mount[i]+1);
		}
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i ++) {
			scanf("%s", flower[i]+1);
		}
		// 求解
		int res = 0;
		for (int i = 1; i <= N; i ++) for (int j = 1; j <= M; j ++) {
			if (check(i, j)) res ++;
		}
		// 输出
		printf("%d\n", res);
	}
	return 0;
}
// 判断是否合法
bool check(int x, int y) {
	for (int i = 1; i <= n; i ++) for (int j = 1; j <= m; j ++) {
		int nx = x + i - n/2 - 1;
		int ny = y + j - m/2 - 1;
		if (is_legal(nx, ny) && mount[nx][ny] == '#' && flower[i][j] == '#') {
			return false;
		}
	}
	return true;
}
// 判断是否越界
inline bool is_legal(int x, int y) {
	return (x >= 1 && x <= N && y >= 1 && y <= M);
}
