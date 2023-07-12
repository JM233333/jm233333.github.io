class Solution {
public:
	int threeSumClosest(vector<int> & nums, int target) {
		// 排序
		sort(nums.begin(), nums.end());
		// 暴力枚举
		int mindelta = INF;
		int res = INF;
		for (int i = 0; i < (int)nums.size() - 2; i ++) {
			// 求解
			int sum = nums[i] + twoSumClosest(nums, i, target - nums[i]);
			// 更新答案
			if (mindelta > abs(target - sum)) {
				mindelta = abs(target - sum);
				res = sum;
			}
		}
		// 返回
		return res;
	}
	// 求解2-sum-closest问题（有序）
	int twoSumClosest(vector<int> & nums, int index, int target) {
		// 主循环
		int mindelta = INF;
		int res = INF;
		int left = index + 1, right = nums.size() - 1;
		while (left < right) {
			// 求和
			int sum = nums[left] + nums[right];
			// 更新答案
			if (mindelta > abs(target - sum)) {
				mindelta = abs(target - sum);
				res = sum;
			}
			if (mindelta == 0) {
				break;
			}
			// 递进
			if (sum < target) left ++;
			if (sum > target) right --;
		}
		// 返回
		return res;
	}
	// 常量
	const int INF = 0x3f3f3f3f;
};
