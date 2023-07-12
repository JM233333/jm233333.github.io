class Solution {
public:
	int uniquePaths(int m, int n) {
		// 特判
		if (m == 1 || n == 1) {
			return 1;
		}
		if (m > n) {
			return uniquePaths(n, m);
		}
		// 初始化
		int C[m + n][m];
		// 递推
		C[0][0] = 0;
		for (int i = 1; i <= m + n - 2; i ++) {
			C[i][0] = 1;
		}
		for (int i = 1; i <= m - 1; i ++) {
			C[i][i] = 1;
		}
		for (int i = 2; i <= m + n - 2; i ++) for (int j = 1; j <= min(i - 1, m - 1); j ++) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
		// 返回
		return C[m + n - 2][m - 1];
	}
};
