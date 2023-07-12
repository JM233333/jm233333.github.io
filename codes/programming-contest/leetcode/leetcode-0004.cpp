class Solution {
public:
	const double INF = 1e9;
public:
	double findMedianSortedArrays(vector<int> & nums1, vector<int> & nums2) {
		// 特判
		if (nums1.size() > nums2.size()) {
			return findMedianSortedArrays(nums2, nums1);
		}
		// 初始化
		int m = nums1.size(), n = nums2.size();
		// 主循环
		double res = 0;
		int left = 0, right = m;
		while (left <= right) {
			// 二分
			int i = (left + right) / 2;
			int j = (m + n) / 2 - i;
			// check
			if (i > 0 && j < n && nums1[i - 1] > nums2[j]) {
				right = i - 1;
			} else if (j > 0 && i < m && nums2[j - 1] > nums1[i]) {
				left = i + 1;
			} else {
				double lmax = max((i == 0 ? -INF : nums1[i - 1]), (j == 0 ? -INF : nums2[j - 1]));
				double rmin = min((i == m ? INF : nums1[i]), (j == n ? INF : nums2[j]));
				if ((m + n) % 2) {
					res = rmin;
				} else {
					res = (lmax + rmin) / 2;
				}
				break;
			}
		}
		// 返回
		return res;
	}
};
