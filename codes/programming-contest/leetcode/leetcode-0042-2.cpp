class Solution {
public:
	int trap(vector<int> & height) {
		// 特判
		if (height.empty()) {
			return 0;
		}
		// 初始化
		int n = height.size();
		int dp_left[n + 5], dp_right[n + 5];
		memset(dp_left, 0, sizeof(dp_left));
		memset(dp_right, 0, sizeof(dp_right));
		dp_left[n - 1] = height[n - 1];
		dp_right[0] = height[0];
		// 递推
		for (int i = n - 2; i >= 0; i --) {
			dp_left[i] = max(dp_left[i + 1], height[i]);
		}
		for (int i = 1; i <= n - 1; i ++) {
			dp_right[i] = max(dp_right[i - 1], height[i]);
		}
		// 求解
		int res = 0;
		for (int i = 0; i <= n - 1; i ++) {
			res += (min(dp_left[i], dp_right[i]) - height[i]);
		}
		// 返回
		return res;
	}
};
