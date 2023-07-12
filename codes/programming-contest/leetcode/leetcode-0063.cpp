class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>> & obstacleGrid) {
		// 初始化
		int m = obstacleGrid.size(), n = obstacleGrid.front().size();
		int dp[m][n];
		// 递推
		dp[0][0] = (obstacleGrid[0][0] == 0 ? 1 : 0);
		for (int i = 1; i < m; i ++) {
			dp[i][0] = (obstacleGrid[i][0] == 0 ? dp[i - 1][0] : 0);
		}
		for (int j = 1; j < n; j ++) {
			dp[0][j] = (obstacleGrid[0][j] == 0 ? dp[0][j - 1] : 0);
		}
		for (int i = 1; i < m; i ++) for (int j = 1; j < n; j ++) {
			dp[i][j] = (obstacleGrid[i][j] == 0 ? dp[i - 1][j] + dp[i][j - 1] : 0);
		}
		// 返回
		return dp[m - 1][n - 1];
	}
};
