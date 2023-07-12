class Solution {
public:
	int largestRectangleArea(vector<int> & heights) {
		// 初始化
		heights.push_back(-1);
		int n = heights.size();
		vector<int> lefts(n), rights(n);
		// 主循环
		stack<int> s;
		for (int i = 0; i < n; i ++) {
			// 出栈
			while (!s.empty() && heights[s.top()] > heights[i]) {
				rights[s.top()] = i - 1;
				s.pop();
			}
			// 入栈
			lefts[i] = (s.empty() ? 0 : s.top() + 1);
			s.push(i);
		}
		// 求最大值
		int res = 0;
		for (int i = 0; i < n - 1; i ++) {
			int area = (rights[i] - lefts[i] + 1) * heights[i];
			res = max(res, area);
		}
		// 返回
		heights.pop_back();
		return res;
	}
};
