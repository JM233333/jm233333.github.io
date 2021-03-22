class Solution {
public:
	string simplifyPath(const string & path) {
		// 解析
		vector<string> stk;
		string cur;
		for (int i = 0; i <= path.length(); i ++) {
			// 获取
			if (i < path.length() && path[i] != '/') {
				cur += path[i];
				continue;
			}
			// 截取
			if (cur == "..") {
				if (!stk.empty()) {
					stk.pop_back();
				}
			} else if (cur != "." && !cur.empty()) {
				stk.push_back(cur);
			}
			cur.clear();
		}
		// 生成
		string res;
		for (auto str : stk) {
			res += "/" + str;
		}
		if (res.empty()) {
			res += "/";
		}
		// 返回
		return res;
	}
};
