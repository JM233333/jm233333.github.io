class Solution {
	typedef long long ll;
public:
	int divide(int dividend, int divisor) {
		// 特判：非法运算
		if (dividend == 0) {
			return 0;
		}
		if (divisor == 0) {
			return MAX;
		}
		// 求解
		ll a = abs((ll)dividend), b = abs((ll)divisor);
		ll res = solve(a, b);
		// 处理符号
		if ((dividend > 0) != (divisor > 0)) {
			res = -res;
		}
		// 处理越界
		if (res < MIN || res > MAX) {
			res = MAX;
		}
		// 返回
		return (int)res;
	}
	// 解决
	ll solve(ll a, ll b) {
		// 主循环
		ll res = 0;
		for (int i = 31; i >= 0; i --) {
			if (a >= (b << i)) {
				a -= (b << i);
				res += (1ll << i);
			}
		}
		// 返回
		return res;
	}
	// 常量
	const int MAX = (1 << 31) - 1;
	const int MIN = (1 << 31);
};
