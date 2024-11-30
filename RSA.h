#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>


int mod(int a, int b)
{
	if (b < 0)
		return -mod(-a, -b);
	int ret = a % b;
	if (ret < 0)
		ret += b;
	return ret;
}
int mod_pow(int num, unsigned int pow, int mod)
{
	int test;
	int n = num;
	for (test = 1; pow; pow >>= 1)
	{
		if (pow & 1)
			test = ((test % mod) * (n % mod)) % mod;
		n = ((n % mod) * (n % mod)) % mod;
	}
	return test;
}
unsigned   int sum_mod(unsigned  int x, unsigned  int y, unsigned  int m) {
	if (m - x > y)
		return  x + y;
	return  y - (m - x);
}
unsigned int mul_mod(unsigned   int x, unsigned   int y, unsigned   int m) {
	if (x > y) {
		unsigned  long  long  int tmp = x;
		x = y;
		y = tmp;
	}
	// x <= y
	unsigned  long  long  int res = 0;
	unsigned  long  long  int iy = y;
	while (x) {
		if (x & 1)
			res = sum_mod(res, iy, m);
		iy = sum_mod(iy, iy, m);
		x >>= 1;
	}
	return  res;
}
unsigned int mod_pow2(unsigned  int x, unsigned  int n, unsigned  int m)
{
	unsigned  long  long  int res = 1;
	while (n) {
		if (n & 1)
			res = mul_mod(res, x, m);
		x = mul_mod(x, x, m);
		n >>= 1;
	}
	return res;

}
int генератор_простых_чисел()
{
	int test;
	for (int i = 0; i < 10000; i++)
	{
		int a = 32768 + rand() % 32768; // [2^15-(2^16-1)]
		test = 0;
		for (int j = 0; j < 100; j++)
		{
			int c = 3 + rand() % 100;
			int b = a % 10;
			if (b != 0 && b != 2 && b != 4 && b != 5 && b != 6 && b != 8)
			{
				if (mod_pow(c, a - 1, a) == 1)
				{
					test++;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
			if (test == 30)
			{
				return a;
			}
		}
	}
}
int gcdExtended(int a, int b, int* x, int* y)
{
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtended(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}
int gcd(int a, int b)
{
	if (a == 0)
		return b;
	return gcd(b % a, a);
}
std::vector<int> RSA(int n, int e, int d)
{
	std::vector<int> result;
	if (n == 0) {
		int p = генератор_простых_чисел();
		int q = генератор_простых_чисел();
		int n = q * p;
		result.push_back(n);
		int fi = (p - 1) * (q - 1);
		int e = 0;
		for (int i = 1; i < 2; i = 1)
		{
			e = 1 + rand() % fi;
			if (gcd(e, fi) == 1 && e % 2 == 1)
			{
				break;
			}
		}
		result.push_back(e);
		int d, y;
		gcdExtended(e, fi, &d, &y);
		d = mod(d, fi);
		result.push_back(d);
	}
	else {
		result.push_back(n);
		result.push_back(e);
		result.push_back(d);
	}
	
	return result;
}
