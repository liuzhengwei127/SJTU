#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <stack>

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

class Information
{
public:
	int day;
	int month;
	int sender;
	int begin;
	vector<Trade>::iterator it;
	vector<Trade>::iterator itLow;
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
			if (line == "")
				break;
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

	stack<Information> last;
	int money;
	int begin = 0;

	while (it != trade.end())
	{
		bool flag = false;
		if (last.size() == 0)
		{
			Information first;
			money = it->getMoney();
			first.begin = 0;
			begin = 0;
			first.day = 31;
			first.month = it->getMonth();
			first.it = it;
			first.itLow = it;
			first.sender = it->getSender();
			last.push(first);

			itLow = it;
			itLow++;

			while (itLow != trade.end() && itLow->getMonth() == last.top().month && itLow->getDay() <= last.top().day && it->getDay() >= begin)
			{
				//&& it->getMoney() == itLow->getMoney()
				if (last.top().sender == it->getSender() && itLow->getAccepter() == last.top().itLow->getSender() && itLow->getSender() == last.top().itLow->getAccepter() && it->getMoney() == money && itLow->getMoney() == money)
				{
					Information tmp;
					tmp.day = itLow->getDay();
					tmp.it = it;
					tmp.itLow = itLow;
					tmp.sender = itLow->getSender();
					tmp.month = it->getMonth();
					tmp.begin = itLow->getDay();
					last.push(tmp);
					circle.push_back(*it);
					circle.push_back(*itLow);
					flag = true;
					break;
				}
				itLow++;
			}

			if (flag)
				continue;

			if (last.size() <= 1)
			{
				if (circle.size() >= 6)
				{
					for (int i = 0; i < circle.size(); i++)
						circle[i].print();
				}
				circle.clear();
				it = last.top().it;
				it++;
				begin = last.top().begin;
				last.pop();
			}
			else
			{
				it = last.top().it;
				itLow = last.top().itLow;
				begin = last.top().begin;
				last.pop();
				it++;
				continue;
			}
		}
		else
		{
			while (it != trade.end() && it->getMonth() == last.top().month && it->getDay() <= last.top().day && it->getDay() >= begin)
			{
				if (last.top().sender != it->getSender())
				{
					it++;
					continue;
				}
				else
				{
					itLow = it;
					itLow++;

					while (itLow != trade.end() && itLow->getMonth() == last.top().month && itLow->getDay() <= last.top().day)
					{
						bool over = false;
						//&& it->getMoney() == itLow->getMoney()
						if (last.top().sender == it->getSender() && itLow->getAccepter() == it->getSender() && itLow->getSender() == it->getAccepter() && it->getMoney() == money && itLow->getMoney() == money)
						{
							if (last.top().it->getSender() == itLow->getSender())
							{
								itLow++;
								continue;
							}
							for (int i = 0; i < circle.size(); i++)
							{
								if (itLow->getAccepter() == circle[i].getAccepter() && itLow->getSender() == circle[i].getSender())
									over = true;
							}

							if (over)
							{
								itLow++;
								continue;
							}
							Information tmp;
							tmp.day = itLow->getDay();
							tmp.it = it;
							tmp.itLow = itLow;
							tmp.sender = itLow->getSender();
							tmp.month = it->getMonth();
							tmp.begin = itLow->getDay();
							last.push(tmp);
							circle.push_back(*it);
							circle.push_back(*itLow);
							flag = true;
							break;
						}
						itLow++;
					}

					if (flag)
						break;
					it++;
				}
			}

			if (flag)
				continue;

			if (last.size() <= 1)
			{
				if (circle.size() >= 6)
				{
					for (int i = 0; i < circle.size(); i++)
						circle[i].print();
					cout << endl<<endl;
				}
				circle.clear();
				it = last.top().it;
				it++;
				begin = last.top().begin;
				last.pop();
			}
			else
			{
				it = last.top().it;
				itLow = last.top().itLow;
				begin = last.top().begin;
				last.pop();
				it++;
				continue;
			}
		}
	}

	system("pause");
	return 0;
}