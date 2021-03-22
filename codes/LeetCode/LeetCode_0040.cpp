class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int> & candidates, int target) {
		// 特判
		if (candidates.empty()) {
			return vector<vector<int>>();
		}
		// 排序
		sort(candidates.begin(), candidates.end());
		// 计数
		vector<pair<int, int>> nctes;
		int val = candidates[0], cnt = 1;
		for (int i = 1; i < candidates.size(); i ++) {
			if (val != candidates[i]) {
				nctes.push_back(pair<int, int>(val, cnt));
				val = candidates[i];
				cnt = 1;
			} else {
				cnt ++;
			}
		}
		nctes.push_back(pair<int, int>(val, cnt));
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(0, target, vec, res, nctes);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int index, int target, vector<int> & vec, vector<vector<int>> & res, const vector<pair<int, int>> & candidates) {
		// 递归终止
		if (target == 0) {
			res.push_back(vec);
			return;
		}
		if (index == candidates.size()) {
			return;
		}
		// 剪枝
		if (target < candidates[index].first) {
			return;
		}
		// 递归
		int m = candidates[index].second;
		for (int i = 0; i <= m; i ++) {
			dfs(index + 1, target - i * candidates[index].first, vec, res, candidates);
			vec.push_back(candidates[index].first);
		}
		for (int i = 0; i <= m; i ++) {
			vec.pop_back();
		}
	}
};
