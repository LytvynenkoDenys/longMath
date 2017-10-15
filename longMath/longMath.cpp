#include <iostream>
#include <string>

using namespace std;

class  longNumeric
{
	public:
		static const long long BASE = 1e9;
		static const long long SIZE = 10;
		long long digits[SIZE];

		longNumeric()
		{
			for (int i = 0; i < SIZE; ++i)
			digits[i] = 0;
		}

		longNumeric(long long x)
		{
			longNumeric();
			int next = 0;
			while (x)
			{
				digits[next++] = x % BASE;
				x /= BASE;
			}
		}
		
		longNumeric& operator=(longNumeric& a)
		{
			for (int i = 0; i < SIZE; ++i)
				digits[i] = a.digits[i];
			return *this;
		}

		void operator+=(longNumeric& a)
		{
			for (int i = 0; i < SIZE; ++i)
				digits[i] += a.digits[i];
			for (int i = 0; i < SIZE - 1; ++i)
			{
				if (digits[i] >= BASE)
				{
					digits[i] -= BASE;
					++digits[i + 1];
				}
			}
		}

		longNumeric& operator+(longNumeric& a)
		{
			longNumeric n(*this);
			n += a;
			return n;
		}

		longNumeric& operator++()
		{
			*this += longNumeric(1);
			return *this;
		}

		void operator-=(longNumeric& a)
		{
			for (int i = 0; i < SIZE; ++i)
				digits[i] -= a.digits[i];
			for (int i = 0; i < SIZE - 1; ++i)
			{
				if (digits[i] < 0)
				{
					digits[i] += BASE;
					--digits[i + 1];
				}
			}
		}

		longNumeric& operator-(longNumeric& a)
		{
			longNumeric n(*this);
			n -= a;
			return n;
		}

		longNumeric& operator--()
		{
			*this -= longNumeric(1);
			return *this;
		}

		void operator*=(longNumeric& a)
		{
			*this = *this * a;
		}

		longNumeric operator*(longNumeric& a)
		{
			longNumeric result;
			for (int i = 0; i < SIZE; ++i)
				for (int j = 0; j < SIZE - i; j++)
					result.digits[i + j] += digits[i] * a.digits[j];
			for (int i = 0; i < SIZE - 1; ++i)
			{
				result.digits[i + 1] += result.digits[i] / BASE;
				result.digits[i] %= BASE;
			}
			return result;
		}

		void operator/=(long long x)
		{
			for (int i = SIZE - 1; i >= 0; --i)
			{
				if (i)
					digits[i - 1] += (digits[i] % x) * BASE;
				digits[i] /= x;
			}
		}

		longNumeric operator/(long long x)
		{
			longNumeric n(*this);
			n /= x;
			return n;
		}
	};

ostream& operator<<(ostream& out, longNumeric& a)
{
	string result;
	char buffer[10];
	for (int i = longNumeric::SIZE - 1; i >= 0; --i)
	{
		sprintf(buffer, "%09d", a.digits[i]);
		result += buffer;
	}
	int first_idx = result.find_first_not_of('0');
	if (first_idx == string::npos)
		out << "0";
	else
		out << result.substr(first_idx);
	return out;
}