class Solution {
public:
	void nextPermutation(vector<int> & nums) {
		// 初始化
		int n = nums.size();
		// 获取变化位置
		int index = n - 2;
		while (index >= 0 && nums[index] >= nums[index + 1]) {
			index --;
		}
		// 特判
		if (index == -1) {
			reverse(nums.begin(), nums.end());
			return;
		}
		// 获取变化位置
		for (int i = n - 1; i >= index + 1; i --) {
			// 交换
			if (nums[index] < nums[i]) {
				swap(nums[index], nums[i]);
				break;
			}
		}
        // 反转
        reverse(nums.begin() + index + 1, nums.end());
	}
};
