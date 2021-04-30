#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;

int hopcroft_karp();
bool bfs();
bool dfs_path(int x);

const int INF = 1e9;
const int MAX = 505;
const int NIL = MAX - 1;

vector<int> graph[MAX];

int matchL[MAX], matchR[MAX];
int distL[MAX];

int n, m, e;

int main() {
	//freopen("test.txt", "r", stdin);
	while (scanf("%d %d %d", &n, &m, &e) != EOF) {
		// 初始化
		for (int i = 0; i < MAX; i ++) {
			graph[i].clear();
		}
		// 输入
		int u, v;
		while (e --) {
			scanf("%d %d", &u, &v);
			graph[u].push_back(v);
		}
		// Hopcrotf-Karp
		int res = hopcroft_karp();
		// 输出
		printf("%d\n", res);
	}
	return 0;
}
// Hopcrotf-Karp
int hopcroft_karp() {
	// 初始化
	for (int i = 0; i < MAX; i ++) {
		matchL[i] = NIL;
		matchR[i] = NIL;
	}
	// 主循环
	int cnt = 0;
	while (bfs()) {
		// 寻找增广路
		for (int x = 1; x <= n; x ++) {
			if (matchL[x] == NIL && dfs_path(x)) {
				cnt ++;
			}
		}
	}
	// 返回
	return cnt;
}
// 广度优先搜索
bool bfs() {
	// 初始化
	queue<int> q;
	for (int x = 1; x <= n; x ++) {
		if (matchL[x] == NIL) {
			q.push(x);
			distL[x] = 0;
		} else {
			distL[x] = INF;
		}
	}
	distL[NIL] = INF;
	// 主循环
	while (!q.empty()) {
		// 出队
		int x = q.front();
		q.pop();
		// 终止
		if (distL[x] > distL[NIL]) {
			break;
		}
		// 遍历右部邻接节点
		for (auto y : graph[x]) {
			// 入队
			if (distL[matchR[y]] == INF) {
				distL[matchR[y]] = distL[x] + 1;
				if (matchR[y] != NIL) {
					q.push(matchR[y]);
				}
			}
		}
	}
	// 返回
	return (distL[NIL] != INF);
}
// 深度优先搜索：寻找增广路
bool dfs_path(int x) {
	// 遍历右部邻接节点
	for (auto y : graph[x]) {
		// 当前为未匹配点，或递归找到一条增广路
		if (distL[matchR[y]] == distL[x] + 1 && (matchR[y] == NIL || dfs_path(matchR[y]))) {
			matchL[x] = y;
			matchR[y] = x;
			return true;
		}
	}
	// 返回
	return false;
}
