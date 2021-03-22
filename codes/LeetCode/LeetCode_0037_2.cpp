class Solution {
public:
	void solveSudoku(vector<vector<char>> & board) {
		// 初始化
		memset(existed_row, false, sizeof(existed_row));
		memset(existed_column, false, sizeof(existed_column));
		memset(existed_square, false, sizeof(existed_square));
		for (int x = 0; x < 9; x ++) for (int y = 0; y < 9; y ++) {
			int z = 3 * (x / 3) + (y / 3);
			if (board[x][y] != '.') {
				int num = board[x][y] - '0';
				set_number(x, y, z, num, true);
			}
		}
		// DFS
		bool flag = false;
		dfs(0, 0, board, flag);
	}
	// 设置数字
	inline void set_number(int x, int y, int z, int num, bool flag) {
		existed_row[x][num] = flag;
		existed_column[y][num] = flag;
		existed_square[z][num] = flag;
	}
	// 深度优先搜索
	void dfs(int x, int y, vector<vector<char>> & board, bool & flag) {
		// 递归终止
		if (flag) {
			return;
		}
		if (y == 9) {
			flag = true;
			return;
		}
		// 获取目标坐标
		int nx = (x + 1) % 9, ny = (x == 8 ? y + 1 : y);
		// 递归
		if (board[x][y] != '.') {
			dfs(nx, ny, board, flag);
			return;
		}
		// 递归
		int z = 3 * (x / 3) + (y / 3);
		for (char ch = '1'; ch <= '9' && !flag; ch ++) {
			int num = ch - '0';
			if (is_legal(x, y, z, num)) {
				set_number(x, y, z, num, true);
				board[x][y] = ch;
				dfs(nx, ny, board, flag);
				if (!flag) {
					set_number(x, y, z, num, false);
					board[x][y] = '.';
				}
			}
		}
	}
	// 判断是否合法
	inline bool is_legal(int x, int y, int z, int num) {
		return (!existed_row[x][num] && !existed_column[y][num] && !existed_square[z][num]);
	}
	// 全局变量
	bool existed_row[9][10];
	bool existed_column[9][10];
	bool existed_square[9][10];
};
