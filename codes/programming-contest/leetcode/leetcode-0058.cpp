class Solution {
public:
	int lengthOfLastWord(const string & s) {
		// 求解
		stringstream ss(s);
		string word;
		int res = 0;
		while (ss >> word) {
			res = word.length();
		}
		// 返回
		return res;
	}
};
