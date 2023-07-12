class Solution {
public:
	vector<vector<int>> threeSum(vector<int> & nums) {
		// 特判
		if (nums.size() < 3) {
			return vector<vector<int>>();
		}
		// 排序
		sort(nums.begin(), nums.end());
		// 暴力枚举
		vector<vector<int>> res;
		for (int i = 0; i < (int)nums.size() - 2; i ++) {
			// 去重
			if (i > 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			// 求解
			vector<vector<int>> vec = twoSum(nums, i, -nums[i]);
			// 更新答案
			res.insert(res.end(), vec.begin(), vec.end());
		}
		// 返回
		return res;
	}
	// 求解2-sum问题（有序）
	vector<vector<int>> twoSum(vector<int> & nums, int index, int target) {
		// 主循环
		vector<vector<int>> res;
		int left = index + 1, right = (int)nums.size() - 1;
		while (left < right) {
			// 求和
			int sum = nums[left] + nums[right];
			// 相等的情况
			if (sum == target) {
				// 更新答案
				res.push_back(vector<int>({nums[index], nums[left], nums[right]}));
				// 递进
				left ++;
				right --;
				// 去重
				while (left < right && nums[left] == nums[left - 1]) { // && left > 0
					left ++;
				}
				while (left < right && nums[right] == nums[right + 1]) { // && right < (int)nums.size() - 1
					right --;
				}
			} else {
				// 递进
				if (sum < target) left ++;
				if (sum > target) right --;
			}
		}
		// 返回
		return res;
	}
};
