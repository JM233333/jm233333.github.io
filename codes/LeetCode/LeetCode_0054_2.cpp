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
		// 遍历
		vector<int> res;
		int len[] = {n, m - 1};
		int x = 0, y = -1;
		int dir = 0;
		while (len[dir % 2] > 0) {
			// 处理当前方向
			for (int i = 0; i < len[dir % 2]; i ++) {
				x += dx[dir];
				y += dy[dir];
				res.push_back(matrix[x][y]);
			}
			// 递进
			len[dir % 2] --;
			dir = (dir + 1) % 4;
		}
		// 返回
		return res;
	}
};
