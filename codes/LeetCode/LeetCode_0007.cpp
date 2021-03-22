class Solution {
public:
	int reverse(int x) {
		// 求解
		int res = 0;
		while (x != 0) {
			// 获取数位
			int digit = x % 10;
			x /= 10;
			// 越界的情况
			if (res > MAXINT / 10 || (res == MAXINT / 10 && digit > MAXINT % 10)) {
				return 0;
			}
			if (res < MININT / 10 || (res == MININT / 10 && digit < MININT % 10)) {
				return 0;
			}
			// 更新答案
			res *= 10;
			res += digit;
		}
		// 返回
		return res;
	}
    // 常量
    const int MAXINT = ~(1 << 31);
    const int MININT = (1 << 31);
};
