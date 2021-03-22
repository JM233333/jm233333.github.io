#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

class Card {
public:
	ll a, b;
	friend bool operator < (const Card & A, const Card & B) {
		if (A.b != B.b) {
			return (A.b < B.b);
		} else {
			return (A.a < B.a);
		}
	}
};

const int MAX = 1e5 + 5;
Card cards[MAX];
multiset<Card> ms;

int main() {
	//freopen("test.txt", "r", stdin);
	int n;
	// 初始化
	ms.clear();
	// 输入
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld %lld", &cards[i].a, &cards[i].b);
	}
	// 排序
	sort(cards+1, cards+1+n, [](const Card & A, const Card & B) {
		if (A.a != B.a) {
			return (A.a > B.a);
		} else {
			return (A.b > B.b);
		}
	});
	// 求解
	for (int i = 1; i <= n; i ++) {
		if (i % 2 == 1) {
			if (!ms.empty() && cards[i].b > ms.begin()->b) {
				ms.erase(ms.begin());
				ms.insert(cards[i]);
			}
		} else {
			ms.insert(cards[i]);
		}
	}
	ll res = 0;
	for (auto card : ms) {
		res += card.b;
	}
	// 输出
	printf("%lld\n", res);
	return 0;
}
