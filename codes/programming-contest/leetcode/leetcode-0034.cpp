class Solution {
public:
	vector<int> searchRange(vector<int> & nums, int target) {
		// 二分查找
		int left = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
		int right = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
		// 特判
		if (left > right) {
			left = -1;
			right = -1;
		}
		// 返回
		return vector<int>({left, right});
	}
};
