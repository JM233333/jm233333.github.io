class Solution {
public:
	string addBinary(const string & a, const string & b) {
		// 初始化
		int n = a.length(), m = b.length();
		if (n < m) {
			return addBinary(b, a);
		}
		// 求解
		string res;
		int rem = 0;
		for (int i = 1; i <= n; i ++) {
			int sum = (a[n - i] - '0') + (i <= m ? (b[m - i] - '0') : 0) + rem;
			rem = sum / 2;
			res += ((sum % 2) + '0');
		}
		if (rem > 0) {
			res += (rem + '0');
		}
		// 返回
		reverse(res.begin(), res.end());
		return res;
	}
};
