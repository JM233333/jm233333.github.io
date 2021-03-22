class Solution {
public:
	int strStr(string haystack, string needle) {
		// 特判
		if (needle.length() == 0) {
			return 0;
		}
		// 初始化
		int fail[needle.length() + 5];
		// KMP
		make_fail(needle, fail);
		return kmp(haystack, needle, fail);
	}
	// 计算fail数组
	void make_fail(const string & mode, int fail[]) {
		// 初始化
		fail[0] = 0;
		// 递推
		for (int i = 1, j = 0; i < mode.length(); i ++) {
			while (j > 0 && mode[i] != mode[j]) {
				j = fail[j - 1];
			}
			if (mode[i] == mode[j]) {
				fail[i] = ++j;
			} else {
				fail[i] = 0;
			}
		}
	}
	// KMP
	int kmp(const string & str, const string & mode, int fail[]) {
		// 递推
		for (int i = 0, j = 0; i < str.length(); i ++) {
			while (j > 0 && str[i] != mode[j]) {
				j = fail[j - 1];
			}
			if (str[i] == mode[j]) {
				j ++;
			}
			if (j == mode.length()) {
				return (i - mode.length() + 1);
			}
		}
		// 返回
		return -1;
	}
};
