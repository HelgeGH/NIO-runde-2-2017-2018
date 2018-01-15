#include <iostream>
#include <algorithm>

using namespace std;

long long MOD = 1000000007;
long long BASE = 2;

long long modMult(long long a, long long b, long long mod) {
	long long ret = 0;
	a %= mod;

	while (b > 0) {
		//Vi har a * b = a + a * (b - 1)
		if (b % 2 == 1) {
			ret = (ret + a) % mod;
			--b;
		}
		//og a * b = 2 * a * (b / 2)
		a = (2 * a) % mod;
		b /= 2;
	}
	return ret;
}

long long sum(long long x) {
	bool isEven = x % 2 == 0;
	long long ret = 0;

	long long a = x + 1;
	long long b = isEven ? x / 2 : (x - 1) / 2;

	ret = modMult(a, b, MOD);

	if (!isEven)
		ret += a / 2;
	return ret % MOD;
}

long long pow(long long base, long long exponent) {
	long long ret = 1;
	while (exponent > 0) {
		//Vi har a^b = a * a^(b-1)
		if (exponent % 2 == 1) {
			ret = (ret * base) % MOD;
			--exponent;
		}
		//og a^b = a^2^(b/2)
		base = (base * base) % MOD;
		exponent /= 2;
	}
	return ret;
}

int main() {
	long long N;
	cin >> N;

	long long result;
	if (N % 2 == 0) {
		long long temp = pow(BASE, N / 2);
		result = temp;
		result %= MOD;
		result += sum(temp - 1) - 1;
	}
	else {
		long long temp = pow(BASE, (N - 1) / 2);
		result = temp;
		result %= MOD;
		result += sum(temp - 1);
		result %= MOD;
		result *= 2;
		result = (result - 1) % MOD;
	}

	cout << result % MOD << endl;
	system("pause");
	return 0;
}