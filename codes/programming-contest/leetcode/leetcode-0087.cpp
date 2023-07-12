class Solution {
public:
	bool isScramble(const string & s1, const string & s2) {
		// 初始化
		int n = s1.length();
		bool dp[n][n][n + 1];
		memset(dp, false, sizeof(dp));
		// 递推
		for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) {
			dp[i][j][1] = (s1[i] == s2[j]);
		}
		for (int len = 2; len <= n; len ++) {
			for (int i = 0; i + len - 1 < n; i ++) for (int j = 0; j + len - 1 < n; j ++) {
				for (int k = 1; k < len; k ++) {
					dp[i][j][len] |= (dp[i][j][k] && dp[i + k][j + k][len - k]);
					dp[i][j][len] |= (dp[i][j + len - k][k] && dp[i + k][j][len - k]);
				}
			}
		}
		// 返回
		return dp[0][0][n];
	}
};
