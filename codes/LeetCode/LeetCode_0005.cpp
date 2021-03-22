class Solution {
public:
	string longestPalindrome(string s) {
		// 特判
		if (s.empty()) {
			return string("");
		}
		// 预处理
		string str;
		str += '#';
		for (int i = 0; i < s.length(); i ++) {
			str += s[i];
			str += '#';
		}
		// 枚举
		int maxlen = 0;
		int index = 0;
		for (int i = 0; i < str.length(); i ++) {
			int len = solve(str, i);
			if (maxlen < len) {
				maxlen = len;
				index = i;
			}
		}
		// 获取答案
		string res;
		for (int i = index - maxlen + 1; i <= index + maxlen - 1; i ++) {
			if (str[i] != '#') {
				res += str[i];
			}
		}
		// 返回
		return res;
	}
	// 获取当前中心的回文半长
	int solve(const string & str, int index) {
		int len = 0;
		while (index - len >= 0 && index + len < str.length()) {
			if (str[index - len] == str[index + len]) {
				len ++;
			} else {
				break;
			}
		}
		return len;
	}
};
