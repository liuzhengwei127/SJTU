#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	int counter = 2;
	int lastnumber;
	cin >> n;

	vector<int> number(n*n, 0);

	lastnumber = n / 2;
	number[lastnumber] = 1;

	while (counter <= n*n)
	{
		if ((lastnumber + 1) % n == 0)
		{
			int tmp = ((lastnumber + n * n) - (2 * n - 1)) % (n*n);
			if (number[tmp] == 0)
			{
				number[tmp] = counter;
				lastnumber = tmp;
			}
			else
			{
				number[(lastnumber + n) % (n*n)] = counter;
				lastnumber = (lastnumber + n) % (n*n);
			}
		}
		else
		{
			int tmp = ((lastnumber + n * n) - (n - 1)) % (n*n);
			if (number[tmp] == 0)
			{
				number[tmp] = counter;
				lastnumber = tmp;
			}
			else
			{
				number[(lastnumber + n) % (n*n)] = counter;
				lastnumber = (lastnumber + n) % (n*n);
			}
		}

		counter++;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << number[n*i + j] << '\t';
		}
		cout << endl;
	}

	return 0;
}