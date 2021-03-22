class Solution {
public:
    string intToRoman(int num) {
    	// 主循环
    	string res;
    	int index = 0;
    	while (num > 0) {
			res += roman[index++][num % 10];
			num /= 10;
    	}
    	// 返回
    	return res;
    }
    // 常量
    const string roman[4][10] = {
		{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
		{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
		{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
		{"", "M", "MM", "MMM"}
	};
};
