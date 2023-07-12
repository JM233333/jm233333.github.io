class Solution {
public:
	bool check(char a, char b) {
		int x = a - '0', y = b - '0';
		int z = x * 10 + y;
		return (x != 0 && z >= 1 && z <= 26);
	}
	int numDecodings(const string & s) {
		// 特判
		if (s[0] == '0') {
			return 0;
		}
		// 初始化
		int n = s.length();
		int dp[n + 5];
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		dp[1] = 1;
		// 递推
		for (int i = 2; i <= n; i ++) {
			if (s[i - 1] != '0') {
				dp[i] += dp[i - 1];
			}
			if (check(s[i - 2], s[i - 1])) {
				dp[i] += dp[i - 2];
			}
			if (dp[i] == 0) {
				return 0;
			}
		}
		// 返回
		return dp[n];
	}
};
