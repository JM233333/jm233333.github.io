#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

class Star {
public:
	int x, y, z;
	Star(int i, int j, int k) : x(i), y(j), z(k) {}
	Star() {}
	friend bool operator < (const Star & A, const Star & B) {
		if (A.x != B.x) {
			return (A.x < B.x);
		} else {
			return (A.z > B.z);
		}
	}
};

const int MAX = 1e5 + 5;
Star stars[MAX];
multiset<int> ms;

int main() {
	//freopen("test.txt", "r", stdin);
	int T;
	int n;
	scanf("%d", &T);
	while (T --) {
		// 初始化
		ms.clear();
		// 输入
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++) {
			scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].z);
		}
		// 排序
		sort(stars+1, stars+1+n);
		// 求解
		int res = 0;
		for (int i = 1; i <= n; i ++) {
			if (stars[i].z == 1) {
				auto it = ms.lower_bound(stars[i].y);
				if (it != ms.begin()) {
					ms.erase(prev(it));
					res ++;
				}
			} else {
				ms.insert(stars[i].y);
			}
		}
		// 输出
		printf("%d\n", res);
	}
	return 0;
}
