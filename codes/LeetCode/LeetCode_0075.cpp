class Solution {
public:
	void sortColors(vector<int> & nums) {
		// 主循环
		int left = 0, right = (int)nums.size() - 1;
		int index = 0;
		while (index <= right) {
			if (nums[index] == 0) {
				swap(nums[index], nums[left]);
				left ++;
				index ++;
			} else if (nums[index] == 1) {
				index ++;
			} else {
				swap(nums[index], nums[right]);
				right --;
			}
		}
	}
};
