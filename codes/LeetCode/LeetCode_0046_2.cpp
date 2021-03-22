class Solution {
public:
	vector<vector<int>> permute(vector<int> & nums) {
		// 排序
		sort(nums.begin(), nums.end());
		// DFS
		vector<bool> visited(nums.size(), false);
		vector<int> perm(nums.size());
		vector<vector<int>> res;
		dfs(0, nums, visited, perm, res);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, vector<int> & nums, vector<bool> & visited, vector<int> & perm, vector<vector<int>> & res) {
		// 递归终止
		if (depth == nums.size()) {
			res.push_back(perm);
			return;
		}
		// 遍历
		for (int i = 0; i < nums.size(); i ++) {
			// 递归
			if (!visited[i]) {
				visited[i] = true;
				perm[depth] = nums[i];
				dfs(depth + 1, nums, visited, perm, res);
				visited[i] = false;
			}
		}
	}
};
