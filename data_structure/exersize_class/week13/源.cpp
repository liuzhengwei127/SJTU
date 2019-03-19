#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>

using namespace std;

class Trade
{
private:
	int sender;
	int accepter;
	double amount;
	int year;
	int month;
	int day;

public:
	Trade() {}
	Trade(int sender, int accepter, double amount, int year, int month, int day) :sender(sender), accepter(accepter),
		amount(amount), year(year), month(month), day(day) {}
	~Trade() {}
	int getSender() { return sender; }
	int getAccepter() { return accepter; }
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	double getMoney() { return amount; }
	void print() { cout << sender << ' ' << accepter << ' ' << amount << ' ' << year << ' ' << month << ' ' << day << endl; }
};

bool dateGap(Trade trade1, Trade trade2, Trade trade3)
{
	if (trade1.getYear() == trade2.getYear() && trade2.getYear() == trade3.getYear() && trade1.getMonth() == trade2.getMonth() && trade2.getMonth() == trade3.getMonth())
		return true;
	else return false;
}

bool cmp(Trade x, Trade y)
{
	if (x.getYear() == y.getYear())
	{
		if (x.getMonth() == y.getMonth())
		{
			return x.getDay() < y.getDay();
		}
		else return x.getMonth() < y.getMonth();
	}
	else return x.getYear() < y.getYear();
}

bool moneyEqual(Trade trade1, Trade trade2, Trade trade3)
{
	if (trade1.getMoney() == trade2.getMoney() && trade2.getMoney() == trade3.getMoney())
		return true;
	else return false;
}

int main()
{
	vector<Trade> trade;

	DWORD time1 = GetTickCount();
	{
		ifstream data("transfer.txt");
		while (!data.eof())
		{
			int sender, accepter, year, month, day;
			double amount;
			char buffer;
			string line;
			data >> sender;
			data >> buffer;
			data >> accepter;
			if (sender == accepter)
			{
				getline(data, line);
				continue;
			}
			data >> buffer;
			data >> amount;
			data >> buffer;
			data >> year;
			data >> buffer;
			data >> month;
			data >> buffer;
			data >> day;
			getline(data, line);
			Trade singleTrade(sender, accepter, amount, year, month, day);
			trade.push_back(singleTrade);
		}
		cout << "Data inputing succeeds." << endl;
		sort(trade.begin(), trade.end(), cmp);
		cout << "Sort succeeds." << endl;
	}
	DWORD time2 = GetTickCount();
	cout << "The run time is:" << (double)(time2 - time1) / 1000 << "s." << endl;

	vector<Trade>::iterator it = trade.begin();
	vector<Trade>::iterator itLow;
	vector<Trade> circle;

	/*while (it != trade.end())
	{
	if (it->getAccepter() == it->getSender())
	{
	it++;
	continue;
	}

	circle.push_back(*it);
	int firstAccepter = it->getAccepter();
	int firstSender = it->getSender();
	vector<Trade>::iterator it1 = ++it;
	while (it1 != trade.end())
	{
	if (it1->getSender() == firstAccepter && it1->getSender() != it1->getAccepter())
	{
	circle.push_back(*it1);
	int secondAccepter = it1->getAccepter();
	vector<Trade>::iterator it2 = ++it1;
	while (it2 != trade.end())
	{
	if (it2->getSender() == secondAccepter && it2->getAccepter() == firstSender)
	{
	if (dateGap(*it, *it1, *it2))// && moneyEqual(*it, *it1, *it2))
	{
	circle[0].print();
	circle[1].print();
	it2->print();
	cout << endl;
	}
	}
	it2++;
	}
	circle.erase(circle.begin() + 1);
	}
	it1++;
	}
	circle.erase(circle.begin());
	it++;
	}*/

	int number = 1;

	while (it != trade.end())
	{
		itLow = ++it;
		int firstSender = it->getSender();
		int firstAccepter = it->getAccepter();
		circle.push_back(*it);
		while (itLow != trade.end())
		{
			if (itLow->getMonth() != it->getMonth())
				break;

			if (itLow->getSender() == firstAccepter && itLow->getAccepter() == firstSender && itLow->getMoney() == it->getMoney())
			{
				circle.push_back(*itLow);
				if (circle.size() >= 3)
				{
					cout << number++ << endl;
					for (int i = 0; i < circle.size(); ++i)
						circle[i].print();
					cout << endl;
				}
				break;
			}

			else if (itLow->getSender() == firstAccepter && itLow->getMoney() == it->getMoney())
			{
				firstAccepter = itLow->getAccepter();
				circle.push_back(*itLow);
			}
			itLow++;
		}
		circle.clear();
	}

	system("pause");
	return 0;
}