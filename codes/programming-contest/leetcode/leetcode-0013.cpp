class Solution {
public:
	int romanToInt(string s) {
		// 主循环
		int res = 0;
		for (int i = 0; i < s.length(); i ++) {
			int num = get_number(s[i]);
			if (i == s.size()-1 || num >= getNumber(s[i+1])) {
				res += num;
			} else {
				res -= num;
			}
		}
		// 返回
		return res;
	}
	// 获取数值
	int get_number(char ch) {
		switch (ch) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		}
		return 0;
	}
};
