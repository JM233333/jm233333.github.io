class Solution {
public:
	int maxArea(vector<int> & height) {
		// 主循环
		int res = 0;
		int left = 0, right = (int)height.size() - 1;
		while (left < right) {
			// 更新答案
			int area = (right - left) * min(height[left], height[right]);
			res = max(res, area);
			// 递进
			if (height[left] < height[right]) {
				left ++;
			} else {
				right --;
			}
		}
		// 返回
		return res;
	}
};
