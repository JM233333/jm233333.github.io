class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int> & nums) {
		// 计数
		map<int, int> mp;
		for (auto x : nums) {
			mp[x] ++;
		}
		vector<pair<int, int>> cnums;
		for (auto p : mp) {
			cnums.push_back(p);
		}
		// DFS
		vector<vector<int>> res;
		vector<int> vec;
		dfs(0, vec, res, cnums);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, vector<int> & vec, vector<vector<int>> & res, const vector<pair<int, int>> & cnums) {
		// 递归终止
		if (depth == cnums.size()) {
			res.push_back(vec);
			return;
		}
		// 递归
		int num = cnums[depth].first, cnt = cnums[depth].second;
		for (int i = 0; i < cnt; i ++) {
			vec.push_back(num);
			dfs(depth + 1, vec, res, cnums);
		}
		for (int i = 0; i < cnt; i ++) {
			vec.pop_back();
		}
		dfs(depth + 1, vec, res, cnums);
	}
};
