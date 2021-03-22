#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

class Edge {
public:
	int st, ed;
	int cost;
	Edge(int i, int j, int c) : st(i), ed(j), cost(c) {}
	Edge() {}
	friend bool operator > (const Edge &E, const Edge &F) {
		return (E.cost > F.cost);
	}
};

const int MAXN = 505, MAX = MAXN*MAXN + 5;
vector<Edge> edges;
int belong[MAX];
int N, M;
int n;

int index(int x, int y);

int kruskal(int n);
void initialize(int n);
int find(int x);
void merge(int x, int y);

int main() {
	//freopen("test.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T --) {
		// 初始化
		edges.clear();
		// 输入
		scanf("%d %d", &N, &M);
		n = index(N, M);
		int sum = 0;
		int a, b;
		for (int i = 1; i <= N; i ++) for (int j = 1; j <= M; j ++) {
			scanf("%d %d", &a, &b);
			if (i+1 <= N) {
				edges.push_back(Edge(index(i, j), index(i+1, j), a));
				sum += a;
			}
			if (j+1 <= M) {
				edges.push_back(Edge(index(i, j), index(i, j+1), b));
				sum += b;
			}
		}
		// Kruskal
		int res = sum - kruskal(n);
		// 输出
		printf("%d\n", res);
	}
	return 0;
}
// 获取节点编号
inline int index(int x, int y) {
	return ((x-1)*M + y);
}
// Kruskal
int kruskal(int n) {
	// 初始化
	initialize(n);
	int cnt = 0;
	// 排序
	sort(edges.begin(), edges.end(), greater<Edge>());
	// 主循环
	int res = 0;
	for (int i = 0; i < edges.size(); i ++) {
		// 获取当前最小边
		Edge &e = edges[i];
		// 是无用边的情况
		if (find(e.st) == find(e.ed)) continue;
		// 合并
		merge(e.st, e.ed);
		// 加权
		res += e.cost;
		cnt ++;
		// 已完成的情况
		if (cnt == n - 1) break;
	}
	// 返回
	return res;
}
// 并查集：初始化
void initialize(int n) {
	for (int i = 0; i <= n; i ++) {
		belong[i] = i;
	}
}
// 并查集；查找
int find(int x) {
	if (belong[x] == x) {
		return x;
	}
	belong[x] = find(belong[x]);
	return belong[x];
}
// 并查集：合并
void merge(int x, int y) {
	int rx = find(x), ry = find(y);
	if (rx != ry) {
		belong[rx] = ry;
	}
}
