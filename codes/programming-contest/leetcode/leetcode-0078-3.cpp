class Solution {
public:
	vector<vector<int>> subsets(vector<int> & nums) {
		// 初始化
		int n = nums.size();
		vector<vector<int>> res;
		// 暴力枚举
		vector<int> vec;
		for (int status = 0; status < (1 << n); status ++) {
			for (int i = 0; i < n; i ++) {
				if ((status >> i) & 1) {
					vec.push_back(nums[i]);
				}
			}
			res.push_back(vec);
			vec.clear();
		}
		// 返回
		return res;
	}
};
