class Solution {
public:
	vector<string> generateParenthesis(int n) {
		// DFS
		vector<string> res;
		string str = "";
		dfs(0, 0, 0, n, str, res);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, int lcnt, int rcnt, const int n, string & str, vector<string> & res) {
		// 递归终止
		if (depth == 2 * n) {
			res.push_back(str);
			return;
		}
		// 递归左括号
		if (lcnt < n) {
			str += '(';
			dfs(depth + 1, lcnt + 1, rcnt, n, str, res);
			str.pop_back();
		}
		// 递归右括号
		if (rcnt < lcnt) {
			str += ')';
			dfs(depth + 1, lcnt, rcnt + 1, n, str, res);
			str.pop_back();
		}
	}
};
