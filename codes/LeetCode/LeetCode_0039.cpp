class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> & candidates, int target) {
		// 排序
		sort(candidates.begin(), candidates.end());
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(0, target, vec, res, candidates);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int index, int target, vector<int> & vec, vector<vector<int>> & res, const vector<int> & candidates) {
		// 递归终止
		if (target == 0) {
			res.push_back(vec);
			return;
		}
		if (index == candidates.size()) {
			return;
		}
		// 剪枝
		if (target < candidates[index]) {
			return;
		}
		// 递归
		int m = target / candidates[index];
		for (int i = 0; i <= m; i ++) {
			dfs(index + 1, target - i * candidates[index], vec, res, candidates);
			vec.push_back(candidates[index]);
		}
		for (int i = 0; i <= m; i ++) {
			vec.pop_back();
		}
	}
};
