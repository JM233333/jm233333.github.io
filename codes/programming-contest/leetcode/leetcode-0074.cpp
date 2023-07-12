class Solution {
public:
	bool searchMatrix(vector<vector<int>> & matrix, int target) {
		// 特判
		if (matrix.empty() || matrix.front().empty()) {
			return false;
		}
		// 初始化
		int m = matrix.size(), n = matrix.front().size();
		// 二分查找行号
		int rid = binary_search_1(matrix, m, n, target);
		if (rid >= m) {
			return false;
		}
		// 二分查找
		bool res = binary_search_2(matrix, m, n, target, rid);
		// 返回
		return res;
	}
	// 二分查找行号
	int binary_search_1(vector<vector<int>> & matrix, int m, int n, int target) {
		int left = 0, right = m - 1;
		int rid = left;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (target > matrix[mid][n - 1]) {
				left = mid + 1;
				rid = left;
			} else {
				right = mid - 1;
			}
		}
		return rid;
	}
	// 二分查找
	bool binary_search_2(vector<vector<int>> & matrix, int m, int n, int target, int rid) {
		int left = 0, right = n - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (target == matrix[rid][mid]) {
				return true;
			}
			if (target > matrix[rid][mid]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return false;
	}
};
