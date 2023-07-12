class Solution {
public:
	bool isPalindrome(int x) {
		// 特判
		if (x < 0) {
			return false;
		}
		if (x % 10 == 0 && x != 0) {
			return false;
		}
		// 主循环
		int y = 0;
		while (x > y) {
			y *= 10;
			y += (x % 10);
			x /= 10;
		}
		// 返回
		return (x == y || x == y / 10);
	}
};
