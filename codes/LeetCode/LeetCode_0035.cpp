class Solution {
public:
	int searchInsert(vector<int> & nums, int target) {
		// 二分查找
		int index = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
		// 返回
		return index;
	}
};
