class Solution {
public:
	string countAndSay(int n) {
		// 求解
		string res = "1";
		for (int t = 1; t <= n - 1; t ++) {
			string str;
			char ch = res[0];
			int cnt = 1;
			for (int i = 1; i < res.length(); i ++) {
				if (res[i] == ch) {
					cnt ++;
				} else {
					// 更新答案
					str += to_string(cnt);
					str += ch;
					// 重置
					ch = res[i];
					cnt = 1;
				}
			}
			// 更新答案
			str += to_string(cnt);
			str += ch;
			res = str;
		}
		// 返回
		return res;
	}
};
