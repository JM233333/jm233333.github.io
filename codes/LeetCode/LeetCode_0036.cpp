class Solution {
public:
	bool isValidSudoku(vector<vector<char>> & board) {
		// 声明
		bool existed[10];
		// 判断行
		for (int i = 0; i < 9; i ++) {
			memset(existed, false, sizeof(existed));
			for (int j = 0; j < 9; j ++) {
				if (!check(board[i][j], i, j, existed)) {
					return false;
				}
			}
		}
		// 判断列
		for (int j = 0; j < 9; j ++) {
			memset(existed, false, sizeof(existed));
			for (int i = 0; i < 9; i ++) {
				if (!check(board[i][j], i, j, existed)) {
					return false;
				}
			}
		}
		// 判断方格
		for (int k = 0; k < 9; k ++) {
			memset(existed, false, sizeof(existed));
			int x = 3 * (k / 3), y = 3 * (k % 3);
			for (int i = x; i < x + 3; i ++) for (int j = y; j < y + 3; j ++) {
				if (!check(board[i][j], i, j, existed)) {
					return false;
				}
			}
		}
		// 返回
		return true;
	}
	// 判断
	bool check(char num, int x, int y, bool existed[]) {
		if (num == '.') {
			return true;
		}
		if (!existed[num - '0']) {
			existed[num - '0'] = true;
			return true;
		}
		return false;
	}
};
