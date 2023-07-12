class Solution {
public:
	string minWindow(const string & s, const string & t) {
		// 初始化
		int cnt_s[256] = {0}, cnt_t[256] = {0};
		int n = s.length();
		// 计数
		int sum = 0;
		for (auto ch : t) {
			if (cnt_t[ch] == 0) {
				sum ++;
			}
			cnt_t[ch] ++;
		}
		// 双指针扫描
		int res[] = {-1, -1};
		int left = 0, right = 0;
		int cnt = 0;
		while (right < n) {
			// 计数
			char ch = s[right];
			cnt_s[ch] ++;
			if (cnt_s[ch] == cnt_t[ch]) {
				cnt ++;
			}
			// 收缩
			while (left <= right && cnt == sum) {
				// 更新答案
				if (res[0] == -1 || (res[1] - res[0]) > (right - left)) {
					res[0] = left;
					res[1] = right;
				}
				// 计数
				char ch = s[left];
				cnt_s[ch] --;
				if (cnt_s[ch] < cnt_t[ch]) {
					cnt --;
				}
				// 递进
				left ++;
			}
			// 递进
			right ++;
		}
		// 返回
		if (res[0] == -1) {
			return "";
		} else {
			return s.substr(res[0], res[1] - res[0] + 1);
		}
	}
};
