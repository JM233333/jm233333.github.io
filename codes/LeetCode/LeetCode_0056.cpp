class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>> & intervals) {
		// 特判
		if (intervals.empty()) {
			return vector<vector<int>>();
		}
		// 排序
		auto cmp = [](const vector<int> & A, const vector<int> & B) {
			return (A[0] < B[0]);
		};
		sort(intervals.begin(), intervals.end(), cmp);
		// 求解
		vector<vector<int>> res;
		res.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); i ++) {
			if (is_crossed(res.back(), intervals[i])) {
				res.back()[1] = max(res.back()[1], intervals[i][1]);
			} else {
				res.push_back(intervals[i]);
			}
		}
		// 返回
		return res;
	}
	// 判断区间是否相交
	inline bool is_crossed(const vector<int> & lhs, const vector<int> & rhs) {
		return (lhs[1] >= rhs[0]);
	}
};
