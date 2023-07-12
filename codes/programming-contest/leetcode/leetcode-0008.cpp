class Solution {
public:
	int myAtoi(string str) {
		// 特判
		if (str.empty()) {
			return 0;
		}
		// 初始化
		int index = 0;
		int res = 0;
		// 处理串首空格
		while (index < str.length() && str[index] == ' ') {
			index ++;
		}
		// 获取符号
		int sign = (str[index] == '-' ? -1 : +1);
		if (str[index] == '-' || str[index] == '+') {
			index ++;
		}
		// 获取数值
		while (index < str.length() && str[index] >= '0' && str[index] <= '9') {
			// 获取数位
			int digit = sign * (str[index] - '0');
			// 越界的情况
			if (res > MAXINT / 10 || (res == MAXINT / 10 && digit > MAXINT % 10)) {
				return MAXINT;
			}
			if (res < MININT / 10 || (res == MININT / 10 && digit < MININT % 10)) {
				return MININT;
			}
			// 递进
			res *= 10;
			res += digit;
			index ++;
		}
		// 返回
		return res;
	}
	// 常量
	const int MAXINT = ~(1 << 31);
	const int MININT = (1 << 31);
};
