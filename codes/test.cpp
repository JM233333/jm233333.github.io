#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;

void floyd_sub(int k);

const int INF = 0x3f3f3f3f;
const int MAX = 205;
int ts[MAX];
int dist[MAX][MAX];
int N;

int main() {
	//freopen("test.txt", "r", stdin);
	int M, Q;
	while (scanf("%d %d", &N, &M) != EOF) {
		// 初始化
		memset(dist, INF, sizeof(dist));
		for (int i = 0; i <= N - 1; i ++) {
			dist[i][i] = 0;
		}
		// 输入
		for (int i = 0; i <= N - 1; i ++) {
			scanf("%d", &ts[i]);
		}
		int u, v, w;
		while (M --) {
			scanf("%d %d %d", &u, &v, &w);
			dist[u][v] = w;
			dist[v][u] = w;
		}
		scanf("%d", &Q);
		// 查询
		int index = 0;
		int x, y, t;
		while (Q --) {
			// 输入
			scanf("%d %d %d", &x, &y, &t);
			// 更新
			while (index <= N - 1 && ts[index] <= t) {
				floyd_sub(index);
				index ++;
			}
			// 输出
			if (ts[x] > t || ts[y] > t || dist[x][y] == INF) {
				printf("%d\n", -1);
			} else {
				printf("%d\n", dist[x][y]);
			}
		}
	}
	return 0;
}
// Floyd子过程
void floyd_sub(int k) {
	for (int i = 0; i <= N - 1; i ++) {
		for (int j = 0; j <= N - 1; j ++) {
			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		}
	}
}
