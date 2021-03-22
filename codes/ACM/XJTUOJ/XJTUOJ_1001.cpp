#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;

class Trie {
public:
	int cnt;
	int next[2];
};

void insert(int x);
void update(int index, int depth);
int query();

const int MAXN = 2e5 + 5, MAXBIT = 32, MAX = MAXN * MAXBIT;
Trie trie[MAX];
int sum1[MAXBIT];
int trcnt;

int main() {
	//freopen("test.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF) {
		// 初始化
		memset(sum1, 0, sizeof(sum1));
		trcnt = 0;
		// 主循环
		int opt;
		int x;
		while (n --) {
			// 输入
			scanf("%d", &opt);
			// 修改
			if (opt == 1) {
				update(0, 0);
			}
			// 插入
			if (opt == 2) {
				scanf("%d", &x);
				insert(x);
			}
			// 输出
			int res = query();
			printf("%d\n", res);
		}
		// 初始化
		memset(trie, 0, (trcnt+1)*sizeof(Trie));
	}
	return 0;
}
// 插入
void insert(int x) {
	int index = 0;
	for (int i = 0; i <= 31; i ++) {
		// 获取子节点
		int k = (x >> i) & 1;
		int & pos = trie[index].next[k];
		// 插入
		if (!pos) {
			pos = ++trcnt;
		}
		trie[index].cnt ++;
		if (k == 1) sum1[i] ++;
		// 递进
		index = pos;
	}
}
// 修改
void update(int index, int depth) {
	// 递归
	if (trie[index].next[1]) {
		update(trie[index].next[1], depth + 1);
	}
	// 更新答案
	if (trie[index].next[0]) sum1[depth] += trie[trie[index].next[0]].cnt;
	if (trie[index].next[1]) sum1[depth] -= trie[trie[index].next[1]].cnt;
	// 更新
	swap(trie[index].next[0], trie[index].next[1]);
}
// 查询
int query() {
	int res = 0;
	for (int i = 0; i <= 31; i ++) {
		res |= ((sum1[i] & 1) << i);
	}
	return res;
}
