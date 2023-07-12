class Solution {
public:
	bool isMatch(const string & s, const string & p) {
		// 初始化
		int n = s.length();
		int m = p.length();
		bool dp[n + 1][m + 1];
        memset(dp, false, sizeof(dp));
		// 递推
		dp[0][0] = true;
		for (int i = 1; i <= n; i ++) {
			dp[i][0] = false;
		}
		for (int j = 1; j <= m && p[j - 1] == '*'; j ++) {
			dp[0][j] = true;
		}
		for (int i = 1; i <= n; i ++) for (int j = 1; j <= m; j ++) {
			if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			} else if (p[j - 1] == '*') {
				dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
			}
		}
		// 返回
		return dp[n][m];
	}
};
