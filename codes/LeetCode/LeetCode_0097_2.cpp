class Solution {
public:
	bool isInterleave(const string & s1, const string & s2, const string & s3) {
		// 特判
		if (s1.length() + s2.length() != s3.length()) {
			return false;
		}
		// 初始化
		int n = s1.length(), m = s2.length();
		bool dp[m + 1];
		memset(dp, false, sizeof(dp));
		// 递推
		dp[0] = true;
		for (int j = 1; j <= m; j ++) {
			dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
		}
		for (int i = 1; i <= n; i ++) {
			dp[0] &= (s1[i - 1] == s3[i - 1]);
			for (int j = 1; j <= m; j ++) {
				dp[j] &= (s1[i - 1] == s3[i + j - 1]);
				dp[j] |= (dp[j - 1] && (s2[j - 1] == s3[i + j - 1]));
			}
		}
		// 返回
		return dp[m];
	}
};