class Solution {
public:
	int removeDuplicates(vector<int> & nums) {
		// 特判
		if (nums.empty()) {
			return 0;
		}
		// 求解
		int n = 1;
		bool flag = false;
		for (int i = 1; i < nums.size(); i ++) {
			if (nums[i] != nums[n - 1] || !flag) {
				flag = (nums[i] == nums[n - 1]);
				nums[n++] = nums[i];
			}
		}
		// 返回
		return n;
	}
};
