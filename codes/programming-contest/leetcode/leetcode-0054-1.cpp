class Solution {
private:
	static constexpr int dx[4] = {0, 1, 0, -1};
	static constexpr int dy[4] = {1, 0, -1, 0};
public:
	vector<int> spiralOrder(vector<vector<int>> & matrix) {
		// 特判
		if (matrix.empty() || matrix.front().empty()) {
			return vector<int>();
		}
		// 初始化
		int m = matrix.size(), n = matrix.front().size();
		bool visited[m][n];
		memset(visited, false, sizeof(visited));
		// 遍历
		vector<int> res;
		int x = 0, y = 0;
		int dir = 0;
		for (int i = 0; i < m * n; i ++) {
			// 更新答案
			res.push_back(matrix[x][y]);
			visited[x][y] = true;
			// 递进
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				dir = (dir + 1) % 4;
				x = x + dx[dir];
				y = y + dy[dir];
			}
		}
		// 返回
		return res;
	}
};
