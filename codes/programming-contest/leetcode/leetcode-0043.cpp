class Solution {
public:
	string multiply(const string & num1, const string & num2) {
		// 初始化
		int n = num1.length();
		int m = num2.length();
		string res(n + m, '0');
		// 求解
		int rem = 0;
		for (int i = n - 1; i >= 0; i --) {
			for (int j = m - 1; j >= 0; j --) {
				int x = (num1[i] - '0') * (num2[j] - '0') + (res[i + j + 1] - '0');
				res[i + j + 1] = (x % 10) + '0';
				res[i + j] += (x / 10);
			}
		}
		// 返回
		for (int i = 0; i < n + m; i ++) {
			if (res[i] != '0') {
				return res.substr(i);
			}
		}
		return "0";
	}
};
