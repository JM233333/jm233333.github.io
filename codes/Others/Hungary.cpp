#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

int hungarian();
bool dfs_path(int x);

const int MAX = 505;
vector<int> graph[MAX];
int match[MAX];
bool visited[MAX];
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
		// Hungarian
		int res = hungarian();
		// 输出
		printf("%d\n", res);
	}
	return 0;
}
// Hungarian
int hungarian() {
	// 初始化
	memset(match, -1, sizeof(match));
	// 遍历
	int cnt = 0;
	for (int x = 1; x <= n; x ++) {
		// 初始化
		memset(visited, false, sizeof(visited));
		// 寻找增广路
		if (dfs_path(x)) cnt ++;
	}
	// 返回
	return cnt;
}
// 深度优先搜索：寻找增广路
bool dfs_path(int x) {
	// 遍历
	for (auto y : graph[x]) {
		// 可访问的情况
		if (!visited[y]) {
			// 已访问标志
			visited[y] = true;
			// 当前为未匹配点，或递归找到一条增广路
			if (match[y] == -1 || dfs_path(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	// 返回
	return false;
}
