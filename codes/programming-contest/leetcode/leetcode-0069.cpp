class Solution {
public:
	int mySqrt(int x) {
		// 特判
		if (x < 2) {
			return x;
		}
		// 二分查找
		int left = 1, right = x / 2;
		int res = 0;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (mid <= x / mid) {
				left = mid + 1;
				res = mid;
			} else {
				right = mid - 1;
			}
		}
		// 返回
		return res;
	}
};
