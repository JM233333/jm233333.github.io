class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string> & strs) {
		// 求解
		unordered_map<string, vector<string>> ump;
		for (auto & str : strs) {
			// 获取有序串
			string sorted = str;
			sort(sorted.begin(), sorted.end());
			// 记录
			ump[sorted].push_back(str);
		}
		// 获取答案
		vector<vector<string>> res;
		for (auto it = ump.begin(); it != ump.end(); it ++) {
			res.push_back(it->second);
		}
		// 返回
		return res;
	}
};
