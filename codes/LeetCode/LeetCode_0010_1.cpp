class Solution {
public:
	bool isMatch(string s, string p) {
		// 初始化
		int n = s.length(), m = p.length();
		bool dp[n + 5][m + 5];
		memset(dp, false, sizeof(dp));
		dp[0][0] = true;
		// 递推
		for (int j = 2; j <= m; j ++) {
			if (p[j - 1] == '*') {
				dp[0][j] = dp[0][j - 2];
			}
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				// 通常匹配
				if (match(s[i - 1], p[j - 1])) {
					dp[i][j] |= dp[i - 1][j - 1];
				}
				// x*匹配
				else if (j >= 2 && p[j - 1] == '*') {
					// 匹配零次
					dp[i][j] |= dp[i][j - 2];
					// 匹配更多一次
					if (match(s[i - 1], p[j - 2])) {
						dp[i][j] |= dp[i - 1][j];
					}
				}
			}
		}
		// 返回
		return dp[n][m];
	}
	// 判断是否匹配
	inline bool match(char si, char pj) {
		return (si == pj || pj == '.');
	}
};
