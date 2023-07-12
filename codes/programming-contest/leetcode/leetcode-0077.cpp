class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(1, vec, res, n, k);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, vector<int> & vec, vector<vector<int>> & res, const int n, const int k) {
		// 递归终止
		if (vec.size() == k) {
			res.push_back(vec);
			return;
		}
		if (depth == n + 1) {
			return;
		}
		// 剪枝
		if (n - depth < k - (vec.size() + 1)) {
			return;
		}
		// 递归
		vec.push_back(depth);
		dfs(depth + 1, vec, res, n, k);
		vec.pop_back();
		dfs(depth + 1, vec, res, n, k);
	}
};
