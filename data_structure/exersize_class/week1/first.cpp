#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	string word;
	string last;
	string next;
	string filename;
	char tmp[50];
	char c;
	char l;
	int line = 0;
	int count = 0;
	int t = 0;
	bool n = false;
	bool no = true;

	cout << "Please input the file name:";
	//cin >> filename;
	filename = "shakespeare.txt";

	ifstream f(filename);
	if (f.is_open())
	{
		cout << "file has been successfully opened.\n";
	}
	else
    {
        cout << "file has not been successfully opened.\n";
        return 1;
    }

    cout << "Please input the word you want to search:";
    cin >> word;

	while (!f.eof())
	{
		c = f.get();

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			tmp[t++] = c;
		}

		else
		{
			tmp[t] = '\0';

			if (n)
			{
				n = false;
				if (no)
				{
					cout << tmp << endl;
				}
				else
				{
					cout << endl;
				}
			}

			if (t >= 1)
			{
				string test = tmp;
				if (tmp == word)
				{
					count++;
					cout << line <<' ';
					if (tmp[0] >= 'a' && tmp[0] <= 'z' && l != ',' && l != '(')
						cout << last << ' ';
					cout << tmp << ' ';
					n = true;
				}
				no = true;

				last = tmp;
			}

			t = 0;

			if (!(c == ' ' || c == '\t'))
			{
				no = false;
			}

			l = c;
		}

		if (c == '\n')
		{
			line++;
		}
	}

	cout << count << endl;

	return 0;
}
