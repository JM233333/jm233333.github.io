class Solution {
public:
	int maximalRectangle(vector<vector<char>> & matrix) {
		// 特判
		if (matrix.empty() || matrix.front().empty()) {
			return 0;
		}
		// 初始化
		int m = matrix.size(), n = matrix.front().size();
		// 遍历
		int res = 0;
		vector<int> heights(n, 0);
		for (int i = 0; i < m; i ++) {
			// 计算高度
			for (int j = 0; j < n; j ++) {
				int x = (matrix[i][j] - '0');
				if (x == 0) {
					heights[j] = 0;
				} else {
					heights[j] += x;
				}
			}
			// 更新答案
			res = max(res, largestRectangleArea(heights));
		}
		// 返回
		return res;
	}
	// 直方图最大矩形
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
