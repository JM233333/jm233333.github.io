class Solution {
public:
	int trap(vector<int> & height) {
		// 特判
		if (height.empty()) {
			return 0;
		}
		// 初始化
		int n = height.size();
		int res = 0;
		// 主循环
		int left = 0, right = n - 1;
		int max_left = 0, max_right = 0;
		while (left < right) {
			if (height[left] < height[right]) {
				max_left = max(max_left, height[left]);
				res += (max_left - height[left]);
				left ++;
			} else {
				max_right = max(max_right, height[right]);
				res += (max_right - height[right]);
				right --;
			}
		}
		// 返回
		return res;
	}
};
