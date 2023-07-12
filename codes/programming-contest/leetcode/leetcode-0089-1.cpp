class Solution {
public:
	vector<int> grayCode(int n) {
		// 生成
		vector<int> res;
		res.push_back(0);
		for (int t = 1; t < (1 << n); t <<= 1) {
			for (int i = 1, j = t - 1; i <= t; i ++, j --) {
				res.push_back(t + res[j]);
			}
		}
		// 返回
		return res;
	}
};
