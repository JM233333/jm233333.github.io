class Solution {
public:
	vector<string> restoreIpAddresses(const string & s) {
		// DFS
		vector<string> vec;
		vector<string> res;
		dfs(0, 0, s, vec, res);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, int index, const string & s, vector<string> & vec, vector<string> & res) {
		// 递归终止
		if (depth == 4) {
			assert(vec.size() == 4);
			string ip;
			for (int i = 0; i < vec.size(); i ++) {
				ip += vec[i];
				if (i != (int)vec.size() - 1) {
					ip += '.';
				}
			}
			res.push_back(ip);
			return;
		}
		if (index >= s.length()) {
			return;
		}
		// 递归
		int val = 0;
		for (int i = index; i < s.length(); i ++) {
			val *= 10;
			val += (s[i] - '0');
			if (val > 255) {
				break;
			}
			if (depth < 3 || i == (int)s.length() - 1) {
				vec.push_back(s.substr(index, i - index + 1));
				dfs(depth + 1, i + 1, s, vec, res);
				vec.pop_back();
			}
			if (val == 0) {
				break;
			}
		}
	}
};