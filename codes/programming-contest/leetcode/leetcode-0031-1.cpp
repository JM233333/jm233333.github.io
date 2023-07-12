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
			sort(nums.begin(), nums.end());
			return;
		}
		// 获取变化位置
		int m = index + 1;
		for (int i = index + 2; i < n; i ++) {
			if (nums[index] < nums[i] && nums[m] > nums[i]) {
				m = i;
			}
		}
		// 交换
		swap(nums[index], nums[m]);
        // 排序
        sort(nums.begin() + index + 1, nums.end());
	}
};
