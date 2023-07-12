class Solution {
public:
	int numDistinct(const string & s, const string & t) {
		// 初始化
		int n = s.length(), m = t.length();
		int dp[n + 1][m + 1];
		memset(dp, 0, sizeof(dp));
		int mod = 1e9 + 7;
		// 递推
		for (int i = 0; i <= n; i ++) {
			dp[i][0] = 1;
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= i && j <= m; j ++) {
				if (s[i - 1] == t[j - 1]) {
					dp[i][j] = dp[i - 1][j] % mod + dp[i - 1][j - 1] % mod;
				} else {
					dp[i][j] = dp[i - 1][j] % mod;
				}
			}
		}
		// 返回
		return dp[n][m];
	}
};