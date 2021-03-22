class Solution {
public:
	int trap(vector<int> & height) {
		// 初始化
		int res = 0;
		// 主循环
		stack<int> s;
		for (int i = 0; i < height.size(); i ++) {
			// 处理
			while (!s.empty() && height[i] >= height[s.top()]) {
				// 出栈
				int index = s.top();
				s.pop();
				// 更新答案
				if (!s.empty()) {
					int dist = i - s.top() - 1;
					res += dist * (min(height[i], height[s.top()]) - height[index]);
				}
			}
			// 入栈
			s.push(i);
		}
		// 返回
		return res;
	}
};
