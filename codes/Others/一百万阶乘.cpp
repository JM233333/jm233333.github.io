#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

namespace FFT {

	class Complex {
	public:
		double real, imag;
		Complex(double r, double i) : real(r), imag(i) {}
		Complex() {}
		friend Complex operator + (const Complex &A, const Complex &B) {
			return Complex(A.real + B.real, A.imag + B.imag);
		}
		friend Complex operator - (const Complex &A, const Complex &B) {
			return Complex(A.real - B.real, A.imag - B.imag);
		}
		friend Complex operator * (const Complex &A, const Complex &B) {
			return Complex(A.real*B.real - A.imag*B.imag, A.real*B.imag + B.real*A.imag);
		}
	};

	//
	const double PI = acos(-1.0);
	const int MAX = 1e7;
	Complex a[4*MAX], b[4*MAX];
	int res[4*MAX];

	// Rader
	void rader(Complex F[], int len) {
		for (int i = 1, j = len/2; i < len-1; i ++) {
			if (i < j) {
				swap(F[i], F[j]);
			}
			int k = len/2;
			while (j >= k) {
				j -= k;
				k /= 2;
			}
			if (j < k) {
				j += k;
			}
		}
	}
	// FFT
	void fft(Complex F[], int len, int t) {
		// Rader
		rader(F, len);
		// ��ѭ��
		for (int h = 2; h <= len; h *= 2) {
			Complex Wn(cos(t*2*PI/h), sin(t*2*PI/h));
			for (int j = 0; j < len; j += h) {
				Complex E(1, 0);
				for (int k = j; k < j + h/2; k ++) {
					Complex u = F[k], v = E * F[k + h/2];
					F[k] = u + v;
					F[k + h/2] = u - v;
					E = E * Wn;
				}
			}
		}
		// IDFT
		if (t == -1) {
			for (int i = 0; i < len; i ++) {
				F[i].real /= len;
			}
		}
	}
	// ���
	string multiply(const string & A, const string & B) {
		// ��ʼ��
		int lenA = A.length(), lenB = B.length();
		int sa = 0, sb = 0;
		while((1 << sa) < lenA) sa ++;
		while((1 << sb) < lenB) sb ++;
		int len = (1 << (max(sa, sb) + 1));
		// ת��Ϊ����
		for (int i = 0; i < len; i ++) {
			a[i] = (i < lenA ? Complex(A[lenA-i-1]-'0', 0) : Complex(0, 0));
			b[i] = (i < lenB ? Complex(B[lenB-i-1]-'0', 0) : Complex(0, 0));
		}
		// DFTת��Ϊ��ֵ����
		fft(a, len, 1);
		fft(b, len, 1);
		// ���ֵ����ĳɳ˷�
		for (int i = 0; i < len; i ++) {
			a[i] = a[i] * b[i];
		}
		// IDFT����ԭ����ϵ��, �鲿һ����0
		fft(a, len, -1);
		// ȡ�����Ĵ���
		for (int i = 0; i < len; i ++) {
			res[i] = (int)(a[i].real + 0.5);
		}
		// ��λ
		for (int i = 0; i < len-1; i ++) {
			res[i+1] += res[i] / 10;
			res[i] %= 10;
		}
		// ����
		string R;
		bool flag = false;
		for (int i = len-1; i >= 0; i --) {
			if (res[i] > 0 || flag) {
				R += (res[i] + '0');
				flag = true;
			}
		}
		return R;
	}
}

class BigInteger {
public:
	string data;
public:
	BigInteger() : data("0") {}
	BigInteger(const string & str) : data(str) {}
	BigInteger(int x) {
		while (x > 0) {
			data += ((x % 10) + '0');
			x /= 10;
		}
		reverse(data.begin(), data.end());
	}
public:
	friend BigInteger operator * (const BigInteger & A, const BigInteger & B) {
		return BigInteger(FFT::multiply(A.data, B.data));
	}
	BigInteger operator ^ (int n) {
		BigInteger res("1");
		BigInteger a = *this;
		while (n > 0) {
			if (n % 2 == 1) res = res * a;
			a = a * a;
			n /= 2;
		}
		return res;
	}
};

const int MAX = 1e6 + 5;
int cnt[MAX];
vector<BigInteger> vec, temp;

void prime_factorize(int l, int r) {
	// ö��
	for (int x = l; x <= r; x ++) {
		// ��ʼ��
		//factors[x].clear();
		// ö������
		int t = x;
		for (int i = 2; i*i <= t; i ++) {
			if (t % i == 0) {
				//factors[x].push_back(i);
				// cnt = 0;
				while (t % i == 0) {
					t /= i;
					cnt[i] ++;
					// cnt ++;
				}
			}
		}
		// ����
		if (t != 1) {
			//factors[x].push_back(t);
			cnt[t] ++;
			// cnt = 1;
		}
	}
}

int main(void) {
	//
	int N = 1e6;
    prime_factorize(2, N);
    //
    for (int i = 2; i <= N; i ++) {
		if (cnt[i] > 0) vec.push_back(BigInteger(i) ^ cnt[i]);
    }
    //
    for (int bound = 100; vec.size() > 1; bound *= 2) {
		BigInteger curr = vec[0];
		for (int i = 1; i < vec.size(); i ++) {
			if (curr.data.length() >= bound) {
				temp.push_back(curr);
				curr = vec[i];
			} else {
				curr = curr * vec[i];
			}
		}
		temp.push_back(curr);
		swap(vec, temp);
		temp = vector<BigInteger>();
    }
    cout << vec[0].data << endl;
    return 0;
}
