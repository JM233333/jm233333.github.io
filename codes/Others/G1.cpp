#pragma G++ optimize ("O2")
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
 
using namespace std;
typedef long long ll;
 
int hungarian();
bool dfs_path(int x);
 
const int MAX = 1e5 + 5;
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
            scanf("%d", &k);
            while (k --) {
                scanf("%d", &y);
                graph[x].push_back(y);
            }
        }
        int res = hungarian();
        printf("%d\n", res);
    }
    return 0;
}
 
int hungarian() {
    memset(match, -1, sizeof(match));
    int cnt = 0;
    for (int x = 1; x <= n; x ++) {
        memset(visited, false, sizeof(visited));
        if (dfs_path(x)) cnt ++;
    }
    return cnt;
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