class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		// 初始化
		int y[n];
		vector<vector<string>> res;
		// DFS
		dfs(0, y, res, n);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int index, int y[], vector<vector<string>> & res, const int n) {
		// 递归终止
		if (index == n) {
			// 绘制答案
			vector<string> solution;
			string row(n, '.');
			for (int i = 0; i < n; i ++) {
				row[y[i]] = 'Q';
				solution.push_back(row);
				row[y[i]] = '.';
			}
			// 更新答案
			res.push_back(solution);
			// 返回
			return;
		}
		// 递归
		for (int i = 0; i < n; i ++) {
			y[index] = i;
			if (is_legal(index, y)) {
				dfs(index + 1, y, res, n);
			}
		}
	}
	// 判断是否合法
	bool is_legal(int index, int y[]) {
		// 遍历行
		for (int i = 0; i < index; i ++) {
			// 同列的情况
			if (y[index] == y[i]) return false;
			// 同对角线的情况
			if (abs(index - i) == abs(y[index] - y[i])) return false;
		}
		// 返回
		return true;
	}
};
