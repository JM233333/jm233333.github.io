class Solution {
public:
	vector<vector<int>> subsets(vector<int> & nums) {
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(0, vec, res, nums);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, vector<int> & vec, vector<vector<int>> & res, const vector<int> & nums) {
		// 递归终止
		if (depth == nums.size()) {
			res.push_back(vec);
			return;
		}
		// 递归
		vec.push_back(nums[depth]);
		dfs(depth + 1, vec, res, nums);
		vec.pop_back();
		dfs(depth + 1, vec, res, nums);
	}
};
