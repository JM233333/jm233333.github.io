class Solution {
public:
	bool isValid(string str) {
		stack<char> s;
		for (auto ch : str) {
			if (ch == '(' || ch =='{' || ch == '[') {
				s.push(ch);
			} else if (!s.empty() && isPair(s.top(), ch)) {
				s.pop();
			} else {
				return false;
			}
		}
		return s.empty();
	}
	// 判断是否配对
	inline bool isPair(char l, char r) {
		return ((l == '(' && r == ')') || (l == '{' && r == '}') || (l == '[' && r == ']'));
	}
};
