class Solution {
public:
	bool isMatch(string s, string p) {
		// 初始化
		int n = s.length(), m = p.length();
		int ** dp = new int * [n + 5];
		for (int i = 0; i < n + 5; i ++) {
			dp[i] = new int[m + 5];
			memset(dp[i], -1, (m + 5) * sizeof(int));
		}
		// DFS
		bool res = dfs(s, p, 0, 0, dp);
		// 释放
		for (int i = 0; i < n + 5; i ++) {
			delete[] dp[i];
		}
		delete[] dp;
		// 返回
		return res;
	}
	// 深度优先搜索
	bool dfs(const string & s, const string & p, int i, int j, int ** dp) {
		// 记忆化搜索
		if (dp[i][j] != -1) {
			return dp[i][j];
		}
		// 递归终止：规则串为空的情况
		else if (j == p.length()) {
			dp[i][j] = (i == s.length());
		}
		// 递归：x*匹配零次的情况
		else if (j + 1 < p.length() && p[j + 1] == '*' && dfs(s, p, i, j + 2, dp)) {
			dp[i][j] = true;
		}
		// 递归终止：输入串为空的情况
		else if (i == s.length()) {
			dp[i][j] = false;
		}
		// 递归终止：匹配失败的情况
		else if (s[i] != p[j] && p[j] != '.') {
			dp[i][j] = false;
		}
		// 递归：x*匹配多次的情况
		else if (j + 1 < p.length() && p[j + 1] == '*') {
			dp[i][j] = dfs(s, p, i + 1, j, dp);
		}
		// 递归
		else {
			dp[i][j] = dfs(s, p, i + 1, j + 1, dp);
		}
		// 返回
		return dp[i][j];
	}
};
