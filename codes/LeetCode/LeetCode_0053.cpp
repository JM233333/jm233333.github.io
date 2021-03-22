class Solution {
public:
	int maxSubArray(vector<int> & nums) {
		// 初始化
		int n = nums.size();
		int res = nums[0];
		// 求解
		int sum = nums[0];
		for (int i = 1; i < nums.size(); i ++) {
			// 递推
			if (sum < 0) {
				sum = nums[i];
			} else {
				sum += nums[i];
			}
			// 更新答案
			res = max(res, sum);
		}
		// 返回
		return res;
	}
};
