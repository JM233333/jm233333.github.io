class Solution {
public:
	int divide(int dividend, int divisor) {
		// 特判：非法运算
		if (dividend == 0) {
			return 0;
		}
		if (divisor == 0) {
			return MAX;
		}
		// 特判：防止 MIN / 1
		if (divisor == 1) {
			return dividend;
		}
		// 特判：防止 x / MIN
		if (divisor == dividend) {
			return 1;
		}
		if (divisor == MIN) {
			return 0;
		}
		// 特判：防止 MIN / -1
		if (dividend == MIN && divisor == -1) {
			return MAX;
		}
		// 求解
		int res;
		if (dividend == MIN) {
			res = solve(abs(dividend + abs(divisor)), abs(divisor)) + 1;
		} else {
			res = solve(abs(dividend), abs(divisor));
		}
		// 处理符号
		if ((dividend > 0) != (divisor > 0)) {
			res = -res;
		}
		// 返回
		return res;
	}
	// 解决
	int solve(int a, int b) {
		// 预处理
		int logk = 0;
		while ((b << logk) <= (MAX >> 1)) {
			logk ++;
		}
		// 主循环
		int res = 0;
		for (int i = logk; i >= 0; i --) {
			if (a >= (b << i)) {
				a -= (b << i);
				res += (1 << i);
			}
		}
		// 返回
		return res;
	}
	// 常量
	const int MAX = (1 << 31) - 1;
	const int MIN = (1 << 31);
};
