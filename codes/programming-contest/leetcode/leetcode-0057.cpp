class Solution {
public:
	vector<vector<int>> insert(vector<vector<int>> & intervals, vector<int> & newInterval) {
		// 预处理
		auto cmp = [](const vector<int> & A, const vector<int> & B) {
			return (A[0] < B[0]);
		};
		auto it = lower_bound(intervals.begin(), intervals.end(), newInterval, cmp);
		intervals.insert(it, newInterval);
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
