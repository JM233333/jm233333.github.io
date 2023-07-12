class Solution {
private:
	static constexpr int dx[4] = {0, 1, 0, -1};
	static constexpr int dy[4] = {1, 0, -1, 0};
public:
	vector<vector<int>> generateMatrix(int n) {
		// 初始化
		vector<vector<int>> res(n, vector<int>(n, 0));
		// 遍历
		int x = 0, y = 0;
		int dir = 0;
		for (int i = 1; i <= n * n; i ++) {
			// 更新答案
			res[x][y] = i;
			// 递进
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx >= 0 && nx < n && ny >= 0 && ny < n && res[nx][ny] == 0) {
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
