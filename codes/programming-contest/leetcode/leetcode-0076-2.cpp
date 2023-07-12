class Solution {
public:
	string minWindow(const string & s, const string & t) {
		// 初始化
		int cnt[256] = {0};
		int n = s.length(), m = t.length();
		// 计数
		for (auto ch : t) {
			cnt[ch] ++;
		}
		// 双指针扫描
		int res[] = {-1, -1};
		int left = 0, right = 0;
		int sum = m;
		while (right < n) {
			// 计数
			char ch = s[right];
			if (cnt[ch] > 0) {
				sum --;
			}
			cnt[ch] --;
			// 收缩
			while (left <= right && sum == 0) {
				// 更新答案
				if (res[0] == -1 || (res[1] - res[0]) > (right - left)) {
					res[0] = left;
					res[1] = right;
				}
				// 计数
				char ch = s[left];
				if (cnt[ch] >= 0) {
					sum ++;
				}
				cnt[ch] ++;
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
