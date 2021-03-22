class Solution {
public:
	int strStr(string haystack, string needle) {
		// 特判
		if (needle.length() == 0) {
			return 0;
		}
		// 求解
		int n = haystack.length(), m = needle.length();
		for (int t = 0; t + m - 1 < n; t ++) {
			// 匹配
			int i = t, j = 0;
			while (j < m && haystack[i] == needle[j]) {
				i ++;
				j ++;
			}
			// 匹配成功的情况
			if (j == m) {
				return t;
			}
		}
		// 返回
		return -1;
	}
};
