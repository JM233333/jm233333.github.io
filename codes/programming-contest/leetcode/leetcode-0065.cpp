class Solution {
public:
	bool isNumber(const string & s) {
		// 特判
		if (s.empty()) {
			return false;
		}
		// 处理前后缀空格
		int left = 0;
		while (left < s.length() && s[left] == ' ') {
			left ++;
		}
		int right = s.length() - 1;
		while (right >= 0 && s[right] == ' ') {
			right --;
		}
		// 处理 xey 的情况
		size_t pos = s.find('e');
		if (pos != string::npos) {
			int mid = pos;
			bool flag_x = is_number(s, left, mid - 1, true);
			bool flag_y = is_number(s, mid + 1, right, false);
			return (flag_x && flag_y);
		}
		// 返回
		return is_number(s, left, right, true);
	}
	// 判断是否为数字
	bool is_number(const string & s, int left, int right, bool allow_float) {
		// 处理符号
		if (s[left] == '+' || s[left] == '-') {
			left ++;
		}
		// 特判
		if (left > right || (left == right && s[left] == '.')) {
			return false;
		}
		// 遍历
		bool has_float = false;
		for (int i = left; i <= right; i ++) {
			// 处理浮点
			if (s[i] == '.') {
				if (allow_float && !has_float) {
					has_float = true;
				} else {
					return false;
				}
			}
			// 处理非法字符
			else if (!isdigit(s[i])) {
				return false;
			}
		}
		// 返回
		return true;
	}
};
