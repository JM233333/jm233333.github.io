class Solution {
private:
	static constexpr int dx[] = {1, -1, 0, 0};
	static constexpr int dy[] = {0, 0, 1, -1};
public:
	bool exist(vector<vector<char>> & board, const string & word) {
		// 特判
		if (word.empty()) {
			return true;
		}
		if (board.empty() || board.front().empty()) {
			return false;
		}
		// 初始化
		int m = board.size(), n = board.front().size();
		vector<vector<bool>> visited;
		for (int i = 0; i < m; i ++) {
			visited.push_back(vector<bool>(n, false));
		}
		// DFS
		for (int i = 0; i < m; i ++) for (int j = 0; j < n; j ++) {
			if (board[i][j] == word[0] && dfs(0, i, j, board, word, m, n, visited)) {
				return true;
			}
		}
		// 返回
		return false;
	}
	// 深度优先搜索
	bool dfs(int depth, int x, int y, vector<vector<char>> & board, const string & word,
			const int m, const int n, vector<vector<bool>> & visited) {
		// 递归终止
		if (depth == word.length() - 1) {
			return true;
		}
		// 递归
		visited[x][y] = true;
		for (int i = 0; i < 4; i ++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == word[depth + 1] && !visited[nx][ny]) {
				if (dfs(depth + 1, nx, ny, board, word, m, n, visited)) {
					return true;
				}
			}
		}
		visited[x][y] = false;
		// 返回
		return false;
	}
};
