class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int> & nums) {
		// 排序
		sort(nums.begin(), nums.end());
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(0, vec, res, nums);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int start, vector<int> & vec, vector<vector<int>> & res, const vector<int> & nums) {
		// 更新答案
		res.push_back(vec);
		// 递归
		for (int i = start; i < nums.size(); i ++) {
			if (i > start && nums[i] == nums[i - 1]) {
				continue;
			}
			vec.push_back(nums[i]);
			dfs(i + 1, vec, res, nums);
			vec.pop_back();
		}
	}
};
