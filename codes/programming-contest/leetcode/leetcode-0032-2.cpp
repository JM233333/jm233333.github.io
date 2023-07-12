class Solution {
public:
	int longestValidParentheses(string s) {
		// 初始化
		int n = s.length();
		int dp[n + 5];
		memset(dp, 0, sizeof(dp));
		// 递推
		for (int i = 1; i < n; i ++) {
			if (s[i] == ')') {
				if (s[i - 1] == '(') {
					dp[i] = get_value(dp, i - 2) + 2;
				} else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
					dp[i] = get_value(dp, i - dp[i - 1] - 2) + dp[i - 1] + 2;
				}
			}
		}
		// 求最大值
		int res = 0;
		for (int i = 0; i < n; i ++) {
			res = max(res, dp[i]);
		}
		// 返回
		return res;
	}
	// 处理向下越界
	inline int get_value(int dp[], int index) {
		return (index >= 0 ? dp[index] : 0);
	}
};
