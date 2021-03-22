#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

bool solve(const string & str);

vector<string> res;

int main() {
	//freopen("test.in", "r", stdin);
	int n;
	string str;
	// 输入
	cin >> n;
	while (n --) {
		// 输入
		cin >> str;
		// 求解
		bool flag = solve(str);
		// 输出
		if (flag) {
			cout << "YES";
			for (int i = 0; i < res.size(); i ++) {
				cout << ' ' << res[i];
			}
			cout << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
// 解决
bool solve(const string & str) {
	// 初始化
	res.clear();
	// 特判
	if (str.length() <= 2 || str.substr(str.length() - 2, 2) != "nb") {
		return false;
	}
	// 处理字符串
	string tmp = "";
	for (int i = 0; i < str.length(); i ++) {
		if (str.substr(i, 2) == "nb") {
			if (tmp == "") {
				return false;
			} else {
				res.push_back(tmp);
				i ++;
				tmp = "";
			}
		} else {
			tmp += str[i];
		}
	}
	// 返回
	return true;
}
