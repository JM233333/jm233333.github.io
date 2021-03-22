class Solution {
public:
    string longestCommonPrefix(vector<string> & strs) {
		// 特判
		if (strs.empty()) {
			return string("");
		}
		// 初始化
		int len = strs[0].length();
		for (int i = 1; i < strs.size(); i ++) {
			len = min(len, (int)strs[i].length());
		}
		// 求解
		for (int i = 1; i < strs.size(); i ++) {
			for (int j = 0; j < min(len, (int)strs[i].length()); j ++) {
				if (strs[i][j] != strs[0][j]) {
					strs[i][j] = '*';
					len = j;
					break;
				}
			}
		}
		// 返回
		return strs[0].substr(0, len);
    }
};
