class Solution {
public:
	int firstMissingPositive(vector<int> & nums) {
		// 求解
		int n = nums.size();
		for (int i = 0; i < n; i ++) {
			while (nums[i] >= 1 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		// 返回
		for (int x = 1; x <= n; x ++) {
			if (x != nums[x - 1]) {
				return x;
			}
		}
		return (n + 1);
	}
};
