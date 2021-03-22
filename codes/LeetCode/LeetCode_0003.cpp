class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// 特判
		if (s.empty()) {
			return 0;
		}
		// 初始化
		bool used[256];
		memset(used, false, sizeof(used));
		// 主循环
		int res = 0;
		int left = 0, right = 0;
		while (right < s.length()) {
			// 递进
			while (used[s[right]]) {
				used[s[left]] = false;
				left ++;
			}
			used[s[right]] = true;
			// 更新答案
			res = max(res, right - left + 1);
			// 递进
			right ++;
		}
		// 返回
		return res;
	}
};
