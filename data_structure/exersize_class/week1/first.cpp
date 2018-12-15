#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string toLower(string word)
{
	for (int i = 0; i < word.size(); i++)
		word[i] = tolower(word[i]);
	return word;
}

int main()
{
	string filename;
	cout << "Please input the file name:";
	//cin >> filename;
	filename = "shakespeare.txt";

	ifstream file(filename);
	if (file.is_open())
	{
		cout << "file has been successfully opened.\n";
	}
	else
	{
		cout << "file has not been successfully opened.\n";
		return 1;
	}

	string word_tofind;
	cout << "Please input the word you want to search:";
	cin >> word_tofind;

	string word;
	string last;
	string now;
	string line;
	int linenumber = 0;
	int count = 0;
	while (getline(file, line))
	{
		linenumber++;
		stringstream ss(line);
		while (ss >> word)
		{
			for (int i = 0; i < word.size(); i++)
			{
				if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')))
				{
					if (word[i] == '-')
						continue;

					if (word[i] == '\'')
					{
						word = word.substr(0, i);
						break;
					}
					else
					{
						word.erase(i);
						i--;
					}
				}
			}

			if (word.size())
			{
				if (now.size() == word_tofind.size() && toLower(now) == toLower(word_tofind))
				{
					cout << linenumber << ": " << last << '\t' << now << '\t' << word << endl;
					count++;
				}
					
				last = now;
				now = word;
			}
		}
	}

	cout << count << endl;

	return 0;
}