class Solution {
public:
	vector<int> findSubstring(string s, vector<string> & words) {
		// 特判
		if (s.length() == 0 || words.empty()) {
			return vector<int>();
		}
		// 初始化
		unordered_map<string, int> ump;
		for (auto word : words) {
			ump[word] ++;
		}
		// 遍历起点
		vector<int> res;
		int n = s.length(), m = words.size(), len = words[0].length();
		for (int i = 0; i < len; i ++) {
			// 主循环
			unordered_map<string, int> cnt;
			int left = i, right = i - len;
			int sum = 0;
			while (right <= n - len) {
				// 递进
				right += len;
				sum ++;
				// 获取子串
				string word = s.substr(right, len);
				// 不合法的情况
				if (ump.find(word) == ump.end()) {
					cnt.clear();
					left = right + len;
					sum = 0;
					continue;
				}
				// 递进
				cnt[word] ++;
				while (left < right && cnt[word] > ump[word]) {
					cnt[s.substr(left, len)] --;
					left += len;
					sum --;
				}
				// 更新答案
				if (sum == m) {
					res.push_back(left);
				}
			}
		}
		// 返回
		return res;
	}
};
