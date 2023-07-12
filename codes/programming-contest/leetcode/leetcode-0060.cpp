class Solution {
public:
	string getPermutation(int n, int k) {
		// 初始化
		vector<int> vec;
		for (int i = 1; i <= n; i ++) {
			vec.push_back(i);
		}
		// 预处理
		int factorial[9 + 1];
		factorial[0] = 1;
		for (int i = 1; i <= n; i ++) {
			factorial[i] = factorial[i - 1] * i;
		}
		// 求解
		string res;
		k --;
		for (int i = 1; i <= n; i ++) {
			// 更新答案
			int idx = k / factorial[n - i];
			res += (vec[idx] + '0');
			// 递进
			k = k % factorial[n - i];
			vec.erase(vec.begin() + idx);
		}
		// 返回
		return res;
	}
};
