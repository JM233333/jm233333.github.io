class Solution {
private:
	const int px[4] = {0, 0, 1, 1};
	const int py[4] = {0, 1, 1, 0};
	const int dx[4] = {0, 1, 0, -1};
	const int dy[4] = {1, 0, -1, 0};
public:
	void rotate(vector<vector<int>> & matrix) {
		// 初始化
		int n = matrix.size();
		int x[4], y[4];
		// 遍历
		for (int d = 0; d < n / 2; d ++) {
			int len = n - 1 - 2*d;
			for (int i = 0; i < len; i ++) {
				// 获取坐标
				for (int j = 0; j < 4; j ++) {
					x[j] = d + len * px[j] + i * dx[j];
					y[j] = d + len * py[j] + i * dy[j];
				}
				// 交换
				for (int j = 1; j < 4; j ++) {
					swap(matrix[x[0]][y[0]], matrix[x[j]][y[j]]);
				}
			}
		}
	}
};
