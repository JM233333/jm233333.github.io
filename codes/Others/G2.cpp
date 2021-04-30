#pragma G++ optimize ("O2")

#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll hungarian();
bool dfs_path(int x);

const ll INF = LLONG_MAX;
const int MAX = 1e5 + 5;
int w[MAX];
vector<int> graph[MAX];
int match[MAX];
bool visited[MAX];
int n, m;

int main() {
	//freopen("test.txt", "r", stdin);
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 0; i < MAX; i ++) {
			graph[i].clear();
		}
		int k, y;
		for (int x = 1; x <= n; x ++) {
			scanf("%d", &w[x]);
			scanf("%d", &k);
			while (k --) {
				scanf("%d", &y);
				graph[x].push_back(y);
			}
		}
		ll res = hungarian();
		printf("%lld\n", res);
	}
	return 0;
}

ll hungarian() {
	memset(match, -1, sizeof(match));
	vector<int> vl;
	for (int x = 1; x <= n; x ++) {
		vl.push_back(x);
	}
	sort(vl.begin(), vl.end(), [](int u, int v) {
		return (w[u] > w[v]);
	});
	for (auto x : vl) {
		memset(visited, false, sizeof(visited));
		dfs_path(x);
	}
	ll res = 0;
	for (int y = 1; y <= m; y ++) {
		if (match[y] != -1) {
			res += w[match[y]];
		}
	}
	return res;
}

bool dfs_path(int x) {
	for (auto y : graph[x]) {
		if (!visited[y]) {
			visited[y] = true;
			if (match[y] == -1 || dfs_path(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}
