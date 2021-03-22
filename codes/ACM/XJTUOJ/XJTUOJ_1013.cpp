#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

void add_edge(int u, int v);
void dfs(int u);

const int MAX = 1e5 + 5;
vector<int> graph[MAX];
bool visited[MAX];
vector<int> res;

int main() {
	//freopen("test.in", "r", stdin);
	int n;
	// 初始化
	for (int i = 0; i < MAX; i ++) {
		graph[i].clear();
	}
	memset(visited, false, sizeof(visited));
	res.clear();
	// 输入
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i <= n-1; i ++) {
		scanf("%d %d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	// 排序
	for (int u = 1; u <= n; u ++) {
		sort(graph[u].begin(), graph[u].end());
	}
	// DFS
	dfs(1);
	// 输出
	for (int i = 0; i < res.size(); i ++) {
		printf("%d", res[i]);
		printf(i == res.size() - 1 ? "\n" : " ");
	}
	return 0;
}
// 加入新边
inline void add_edge(int u, int v) {
	graph[u].push_back(v);
}
// 深度优先搜索
void dfs(int u) {
	// 更新
	visited[u] = true;
	res.push_back(u);
	// 递归
	for (int i = 0; i < graph[u].size(); i ++) {
		int v = graph[u][i];
		if (!visited[v]) {
			dfs(v);
		}
	}
}
