class Solution {
public:
	bool search(vector<int> & nums, int target) {
		// 二分查找
		int left = 0, right = (int)nums.size() - 1;
		while (left <= right) {
			// 获取中间点
			int mid = (left + right) / 2;
			// 找到的情况
			if (nums[mid] == target || nums[left] == target || nums[right] == target) {
				return true;
			}
			// 暴力
			if (nums[left] == nums[mid]) {
				left ++;
				continue;
			}
			// 分类讨论
			if (nums[left] < nums[right]) {
				if (target < nums[mid]) {
					right = mid - 1;
				} else {
					left = mid + 1;
				}
			} else if (nums[mid] > nums[left]) {
				if (target > nums[left] && target < nums[mid]) {
					right = mid - 1;
				} else {
					left = mid + 1;
				}
			} else {
				if (target > nums[mid] && target < nums[right]) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
		}
		// 返回
		return false;
	}
};
