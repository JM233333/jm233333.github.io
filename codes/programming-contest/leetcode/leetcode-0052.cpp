class Solution {
public:
	int totalNQueens(int n) {
		// 初始化
		int y[n];
		int res = 0;
		// DFS
		dfs(0, y, res, n);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int index, int y[], int & res, const int n) {
		// 递归终止
		if (index == n) {
			res ++;
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
