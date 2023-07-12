class Solution {
public:
	vector<vector<int>> permute(vector<int> & nums) {
		// 排序
		sort(nums.begin(), nums.end());
		// 求解
		vector<vector<int>> res;
		do {
			res.push_back(nums);
		} while (next_permutation(nums.begin(), nums.end()));
		// 返回
		return res;
	}
};
