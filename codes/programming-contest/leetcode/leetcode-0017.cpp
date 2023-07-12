class Solution {
public:
	vector<string> letterCombinations(string digits) {
		// 特判
		if (digits.length() == 0) {
			return vector<string>();
		}
		// DFS
		vector<string> res;
		string str = "";
		dfs(0, str, res, digits);
		// 返回
		return res;
	}
	// 深度优先搜索
	void dfs(int depth, string & str, vector<string> & res, const string & digits) {
		// 递归终止
		if (depth == digits.length()) {
			res.push_back(str);
			return;
		}
		// 递归
		const string & lst = mp[digits[depth] - '2'];
		for (int i = 0; i < lst.length(); i ++) {
			str += lst[i];
			dfs(depth + 1, str, res, digits);
			str.pop_back();
		}
	}
	// 常量
	const vector<string> mp = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};
