class Solution {
public:
	int longestValidParentheses(string s) {
		// 初始化
		int res = 0;
		// 正向求解
		res = max(res, solve(s, '('));
		// 反向求解
		reverse(s.begin(), s.end());
		res = max(res, solve(s, ')'));
		// 返回
		return res;
	}
	// 解决
	int solve(const string & s, const char lch) {
		// 初始化
		int res = 0;
		// 主循环
		int lcnt = 0, rcnt = 0;
		for (int i = 0; i < s.length(); i ++) {
			// 统计
			if (s[i] == lch) {
				lcnt ++;
			} else {
				rcnt ++;
			}
			// 更新答案
			if (lcnt == rcnt) {
				res = max(res, lcnt + rcnt);
			}
			// 清空
			if (lcnt < rcnt) {
				lcnt = 0;
				rcnt = 0;
			}
		}
		// 返回
		return res;
	}
};
