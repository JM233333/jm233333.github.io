class Solution {
public:
	vector<int> grayCode(int n) {
		// 生成
		vector<int> res(1 << n);
		for (int i = 0; i < (1 << n); i ++) {
			res[i] = i ^ (i >> 1);
		}
		// 返回
		return res;
	}
};
