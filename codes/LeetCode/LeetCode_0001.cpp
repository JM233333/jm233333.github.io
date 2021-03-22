class Solution {
public:
	vector<int> twoSum(vector<int> & nums, int target) {
		// 求解
		unordered_map<int, int> ump;
		for (int i = 0; i < nums.size(); i ++) {
			// 查找
			int val = target - nums[i];
			if (ump.find(val) != ump.end()) {
				return vector<int>({ump[val], i});
			}
			// 插入
			ump[nums[i]] = i;
		}
		// 返回
		return vector<int>({-1, -1});
	}
};
