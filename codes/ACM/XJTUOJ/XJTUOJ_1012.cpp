#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

class Point {
public:
	double x, y;
	Point(double i, double j) : x(i), y(j) {}
	Point() {}
	friend Point operator - (const Point & A, const Point & B) {
		return Point(A.x - B.x, A.y - B.y);
	}
	friend double operator * (const Point & A, const Point & B) {
		return (A.x*B.x + A.y*B.y);
	}
	friend inline double dist2(const Point & A, const Point & B) {
		Point v = A - B;
		return (v * v);
	}
};

const int MAX = 105;
Point points[MAX];

int main() {
	//freopen("test.in", "r", stdin);
	int n;
	double r;
	// 输入
	scanf("%d %lf", &n, &r);
	for (int i = 1; i <= n; i ++) {
		scanf("%lf %lf", &points[i].x, &points[i].y);
	}
	// 求解
	double res = 0;
	for (int i = 2; i <= n; i ++) {
		// 获取相邻点
		int h = i - 1;
		int j = i % n + 1;
		// 获取边长
		double a2 = dist2(points[h], points[i]), a = sqrt(a2);
		double b2 = dist2(points[i], points[j]), b = sqrt(b2);
		double c2 = dist2(points[h], points[j]);
		// 计算角度
		double k1 = acos((a / 2) / r);
		double k2 = acos((b / 2) / r);
		double theta = acos((a2 + b2 - c2) / (2 * a * b));
		double alpha = k1 + k2 - theta;
		// 计算弧长
		double len = sqrt(dist2(points[1], points[i]));
		double arc = alpha * len;
		res += arc;
	}
	// 输出
	printf("%.6f\n", res);
	return 0;
}
