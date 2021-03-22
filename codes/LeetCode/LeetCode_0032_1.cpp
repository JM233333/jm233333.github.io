class Solution {
public:
	int longestValidParentheses(string s) {
		// 初始化
		int res = 0;
		// 主循环
		stack<int> stk;
		stk.push(-1);
		for (int i = 0; i < s.length(); i ++) {
			if (s[i] == '(') {
				// 入栈
				stk.push(i);
			} else {
				// 出栈
				stk.pop();
				// 更新
				if (stk.empty()) {
					stk.push(i);
				} else {
					res = max(res, i - stk.top());
				}
			}
		}
		// 返回
		return res;
	}
};
