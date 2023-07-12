class Solution {
private:
	const int MIN = (1 << 31);
public:
	double myPow(double x, int n) {
		double res;
		if (n >= 0) {
			res = power(x, n);
		} else {
			res = 1.0 / (n == MIN ? (power(x, abs(n + 1)) * x) : power(x, abs(n)));
		}
		return res;
	}
	// 快速幂
	double power(double a, int n) {
		double res = 1;
		while (n > 0) {
			if (n & 1) res = res * a;
			a = a * a;
			n >>= 1;
		}
		return res;
	}
};
