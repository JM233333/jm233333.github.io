#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long ll;

ll solve();
bool is_operator(char ch);
int get_priority(char opt);
ll power(ll a, ll b);

const int MAX = 105;
string str;
stack<ll> stk_num, stk_opt, s;
vector<ll> v;
bool flag;

int main() {
	//freopen("test.in", "r", stdin);
	//while (scanf("%[^\n]", str) != EOF) {
		getline(cin, str);
		// 初始化
		while (!stk_num.empty()) {
			stk_num.pop();
		}
		while (!stk_opt.empty()) {
			stk_opt.pop();
		}
		v.clear();
		flag = true;
		// 求解
		ll res = solve();
		// 输出
		if (flag) {
			printf("%lld\n", res);
		} else {
			printf("Error\n");
		}
	//}
	return 0;
}
// 解决
ll solve() {
	// 主循环
	int i = 0;
	bool prev_opt = true, is_negative = false;
	while (i < str.length()) {
		// 清除空格
		while (i < str.length() && str[i] == ' ') {
			i ++;
		}
		if (i == str.length()) {
			break;
		}
		// 处理操作数
		if (isdigit(str[i])) {
			ll x = 0;
			while (isdigit(str[i])) {
				x *= 10;
				x += (str[i] - '0');
				i ++;
			}
			if (is_negative) {
				is_negative = false;
				x *= -1;
			}
			v.push_back(x);
			prev_opt = false;// printf("{%lld}", x);
		}
		// 清除空格
		while (i < str.length() && str[i] == ' ') {
			i ++;
		}
		if (i == str.length()) {
			break;
		}
		// 处理单元运算符
		while (i < str.length() && str[i] == '-' && prev_opt) {// printf("{NEG}");
			is_negative = !is_negative;
			i ++;
			while (i < str.length() && str[i] == ' ') {
				i ++;
			}
		}
		if (i == str.length()) {
			break;
		}
		// 处理二元运算符
		if (is_operator(str[i])) {// printf("{%c}",str[i]);
			while (!stk_opt.empty() && get_priority(stk_opt.top()) >= get_priority(str[i]) && !(stk_opt.top() == str[i] && str[i] == '^')) {
				v.push_back(stk_opt.top());
				stk_opt.pop();
			}
			stk_opt.push(str[i]);
			prev_opt = true;
		} else if (str[i] == '(') {
			stk_opt.push(str[i]);
			prev_opt = true;
		} else if (str[i] == ')') {
			bool matched = false;
			while (!stk_opt.empty()) {
				if (stk_opt.top() == '(') {
					matched = true;
					break;
				}
				v.push_back(stk_opt.top());
				stk_opt.pop();
			}
			if (!matched) {
				flag = false;
				break;
			}
			stk_opt.pop();
			prev_opt = true;
		} else i--;
		i ++;
	}
	// 处理剩余运算符
	while (!stk_opt.empty()) {
		if (stk_opt.top() == '(') {
			flag = false;
			break;
		}
		v.push_back(stk_opt.top());
		stk_opt.pop();
	}
	// 计算后缀表达式
	/*for (int i = 0; i < v.size(); i ++) {
		if (is_operator(v[i])) printf("%c", v[i]);
		else printf("%lld", v[i]);
	} printf("\n");*/
	while (!s.empty()) {
		s.pop();
	}
	ll a, b, c;
	for (int i = 0; i < v.size(); i ++) {
		if (is_operator(v[i])) {
			if (!s.empty()) {
				b = s.top();
				s.pop();
			}
			if (!s.empty()) {
				a = s.top();
				s.pop();
			}
			if (v[i] == '+') c = a + b;
			if (v[i] == '-') c = a - b;
			if (v[i] == '*') c = a * b;
			if (v[i] == '/') {
				if (b == 0) {
					flag = false;
					break;
				}
				c = a / b;
			}
			if (v[i] == '^') c = power(a, b);
			s.push(c);
		} else {
			s.push(v[i]);
		}
	}
	ll res = s.top();
	s.pop();
	return res;
}
// 判断是否为运算符
inline bool is_operator(char ch) {
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
// 获取运算符优先级
int get_priority(char opt) {
	if (opt == '(') {
		return -1;
	}
	if (opt == '+' || opt == '-') {
		return 1;
	}
	if (opt == '*' || opt == '/') {
		return 2;
	}
	if (opt == '^') {
		return 3;
	}
	if (opt == ')') {
		return 999;
	}
	return 0;
}
// 快速幂
ll power(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b % 2 == 1) res *= a;
		a *= a;
		b /= 2;
	}
	return res;
}
