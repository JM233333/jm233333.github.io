class Solution {
public:
	vector<vector<int>> fourSum(vector<int> & nums, int target) {
		// 特判
		if (nums.size() < 4) {
			return vector<vector<int>>();
		}
		// 排序
		sort(nums.begin(), nums.end());
		// 暴力枚举
		vector<vector<int>> res;
		int n = nums.size();
		for (int i = 0; i < n - 3; i ++) {
			// 去重
			if (i > 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			// 剪枝
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
				break;
			}
			if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) {
				continue;
			}
			// 暴力枚举
			for (int j = i + 1; j < n - 2; j ++) {
				// 去重
				if (j > i + 1 && nums[j] == nums[j - 1]) {
					continue;
				}
				// 剪枝
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
					break;
				}
				if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target) {
					continue;
				}
				// 求解
				vector<vector<int>> vec = twoSum(nums, i, j, target - nums[i] - nums[j]);
				// 更新答案
				res.insert(res.end(), vec.begin(), vec.end());
			}
		}
		// 返回
		return res;
	}
	// 求解2-sum问题（有序）
	vector<vector<int>> twoSum(vector<int> & nums, int index1, int index2, int target) {
		// 主循环
		vector<vector<int>> res;
		int left = index2 + 1, right = (int)nums.size() - 1;
		while (left < right) {
			// 求和
			int sum = nums[left] + nums[right];
			// 相等的情况
			if (sum == target) {
				// 更新答案
				res.push_back(vector<int>({nums[index1], nums[index2], nums[left], nums[right]}));
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
