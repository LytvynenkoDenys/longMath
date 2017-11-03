#include <iostream>
#include <string>

using namespace std;
static const int N = 6;
static const int BASE = pow(10, N);

class  longNumeric
{
	public:
		int count;
		int sizeOfarray;
		long long *arr;
		longNumeric(string s)
		{
			int temp = s.length();
			count = temp / 6 + 1;
			arr = new long long[count];
			for (int i = 0; i < count - 1; ++i)
			{
				arr[i] = 0;
				int p = 1;
				for (int j = 0; j < (i < count - 1 ? 6 : (temp % 6)); ++j)
				{
					arr[i] += s[temp - i*6 - 1 - j] * p;
					p *= 10;
				}
			}
		}
};

int main()
{
	string s;
	cin >> s;
	longNumeric a(s);
	for (int i = 0; i < a.count; ++i)
		cout << a.arr[i] << endl;
	system("pause");
	return 0;
}