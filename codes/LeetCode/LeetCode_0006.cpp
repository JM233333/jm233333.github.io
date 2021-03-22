class Solution {
public:
	string convert(string s, int numRows) {
		// 初始化
		string box[numRows];
		// 模拟
		int column = 0;
		int index = 0;
		while (index < s.length()) {
			if (column % 2 == 0) {
				for (int i = 0; i <= numRows - 1 && index < s.length(); i ++) {
					box[i] += s[index++];
				}
			} else {
				for (int i = numRows - 2; i >= 1 && index < s.length(); i --) {
					box[i] += s[index++];
				}
			}
			column ++;
		}
		// 获取答案
		string res;
		for (int i = 0; i < numRows; i ++) {
			res += box[i];
		}
		// 返回
		return res;
	}
};
