class Solution {
public:
	void setZeroes(vector<vector<int>> & matrix) {
		// 特判
		if (matrix.empty()) {
			return;
		}
		// 初始化
		int m = matrix.size(), n = matrix.front().size();
		// 预处理
		bool column0 = false;
		for (int i = 0; i < m; i ++) {
			if (matrix[i][0] == 0) {
				column0 = true;
				break;
			}
		}
		bool row0 = false;
		for (int j = 0; j < n; j ++) {
			if (matrix[0][j] == 0) {
				row0 = true;
				break;
			}
		}
		for (int i = 1; i < m; i ++) for (int j = 1; j < n; j ++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
		// 染色
		for (int i = 1; i < m; i ++) for (int j = 1; j < n; j ++) {
			if (matrix[i][0] == 0 || matrix[0][j] == 0) {
				matrix[i][j] = 0;
			}
		}
		if (column0) for (int i = 0; i < m; i ++) {
			matrix[i][0] = 0;
		}
		if (row0) for (int j = 0; j < n; j ++) {
			matrix[0][j] = 0;
		}
	}
};
