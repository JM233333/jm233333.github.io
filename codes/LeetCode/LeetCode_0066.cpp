class Solution {
public:
	vector<int> plusOne(vector<int> & digits) {
		// 初始化
		int n = digits.size();
		vector<int> res;
		// 求解
		bool added = true;
		for (int i = n - 1; i >= 0; i --) {
			if (added) {
				int x = digits[i] + 1;
				res.push_back(x % 10);
				added = (x == 10);
			} else {
				res.push_back(digits[i]);
			}
		}
		if (added) {
			res.push_back(1);
		}
		// 返回
		reverse(res.begin(), res.end());
		return res;
	}
};
