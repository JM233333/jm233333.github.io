class Solution {
public:
	int climbStairs(int n) {
		// 初始化
		int dp[n + 1];
		dp[0] = 1;
		dp[1] = 1;
		// 递推
		for (int i = 2; i <= n; i ++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		// 返回
		return dp[n];
	}
};
