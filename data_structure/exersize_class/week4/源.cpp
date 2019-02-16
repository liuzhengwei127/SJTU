#include<iostream>
#include<ctime>
#include<fstream>
#include<string>

using namespace std;

char buffer[1000];
float price;
float amount_b = 0, amount_g = 0;
int counter_b = 0, counter_g = 0;

int count(ifstream &file)
{
	int counter = 0;
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file.getline(buffer,1000))
	{
		counter++;
	}

	return counter;
}

bool findbuyer(string buyerid_toget, ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		if (str.size() > 7)
		{
			tmp = str.substr(0, 7);
		}
		else
		{
			continue;
		}

		if (tmp == "buyerid")
		{
			string buyerid = str.erase(0, 8);

			if (buyerid == buyerid_toget)
			{
				while (file >> str)
				{
					string tmp;
					if (str.size() > 9)
					{
						tmp = str.substr(0, 9);
					}
					else
					{
						continue;
					}

					if (tmp == "buyername")
					{
						string buyername = str.erase(0, 10);
						cout << buyername << endl;
						return true;
					}
				}
				return true;
			}
		}
	}

	return false;
}

bool findgood(string goodid_toget, ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		if (str.size() > 6)
		{
			tmp = str.substr(0, 6);
		}
		else
		{
			continue;
		}

		if (tmp == "goodid")
		{
			string goodid = str.erase(0, 7);

			if (goodid == goodid_toget)
			{
				while (file >> str)
				{
					string tmp;
					if (str.size() > 9)
					{
						tmp = str.substr(0, 9);
					}
					else
					{
						continue;
					}

					if (tmp == "good_name")
					{
						string goodname = str.erase(0, 10);
						cout << goodname << endl;

						while (file >> str)
						{
							string tmp;
							if (str.size() > 5)
							{
								tmp = str.substr(0, 5);
							}
							else
							{
								continue;
							}

							if (tmp == "price")
							{
								string pricestring = str.erase(0, 6);
								price = atof(pricestring.c_str());
								return true;
							}
						}
						return true;
					}
				}
				return true;
			}
		}
	}

	return false;
}

bool findgood_b(string goodid_toget, ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		if (str.size() > 6)
		{
			tmp = str.substr(0, 6);
		}
		else
		{
			continue;
		}

		if (tmp == "goodid")
		{
			string goodid = str.erase(0, 7);

			if (goodid == goodid_toget)
			{
				while (file >> str)
				{
					string tmp;
					if (str.size() > 9)
					{
						tmp = str.substr(0, 9);
					}
					else
					{
						continue;
					}

					if (tmp == "good_name")
					{
						string goodname = str.erase(0, 10);

						while (file >> str)
						{
							string tmp;
							if (str.size() > 5)
							{
								tmp = str.substr(0, 5);
							}
							else
							{
								continue;
							}

							if (tmp == "price")
							{
								string pricestring = str.erase(0, 6);
								price = atof(pricestring.c_str());
								return true;
							}
						}
						return true;
					}
				}
				return true;
			}
		}
	}

	return false;
}

bool findorder(string orderid_toget,ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		float amount;

		if (str.size() > 7)
		{
			tmp = str.substr(0, 7);
		}
		else
		{
			continue;
		}

		if (tmp == "orderid")
		{
			string orderid = str.erase(0, 8);

			if (orderid == orderid_toget)
			{
				string buyerid_toget;
				string goodid_toget;

				ifstream buyer1("buyer.0.0");
				ifstream buyer2("buyer.1.1");
				ifstream good1("good.0.0");
				ifstream good2("good.1.1");
				ifstream good3("good.2.2");

				file >> buyerid_toget;
				file >> buyerid_toget;
				buyerid_toget = buyerid_toget.erase(0, 8);
				file >> goodid_toget;
				goodid_toget = goodid_toget.erase(0, 7);



				if (!findbuyer(buyerid_toget,buyer1))
					findbuyer(buyerid_toget,buyer2);

				if (!findgood(goodid_toget, good1))
					if (!findgood(goodid_toget, good2))
						findgood(goodid_toget, good3);

				file >> goodid_toget;

				if (goodid_toget[0] != 'a')
					file >> goodid_toget;

				goodid_toget = goodid_toget.erase(0, 7);

				amount = atoi(goodid_toget.c_str());

				cout << amount << '\t';
				cout << price << endl;
				cout << price * amount << endl;

				return true;
			}
		}
	}

	return false;
}

void findorder_b(string buyerid_toget, ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		float amount;

		if (str.size() > 7)
		{
			tmp = str.substr(0, 7);
		}
		else
		{
			continue;
		}

		if (tmp == "buyerid")
		{
			string buyerid = str.erase(0, 8);

			if (buyerid == buyerid_toget)
			{
				counter_b++;

				string goodid_toget;
				file >> goodid_toget;
				goodid_toget = goodid_toget.erase(0, 7);

				ifstream good1("good.0.0");
				ifstream good2("good.1.1");
				ifstream good3("good.2.2");

				if (!findgood_b(goodid_toget, good1))
					if (!findgood_b(goodid_toget, good2))
						findgood_b(goodid_toget, good3);

				file >> goodid_toget;

				if (goodid_toget[0] != 'a')
					file >> goodid_toget;

				goodid_toget = goodid_toget.erase(0, 7);

				amount = atoi(goodid_toget.c_str());

				amount_b += amount * price;
			}
		}
	}
}

void findorder_g(string goodid_toget, ifstream &file)
{
	string str;

	if (!file.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	while (file >> str)
	{
		string tmp;
		float amount;

		if (str.size() > 6)
		{
			tmp = str.substr(0, 6);
		}
		else
		{
			continue;
		}

		if (tmp == "goodid")
		{
			string goodid = str.erase(0, 7);

			if (goodid == goodid_toget)
			{
				string tmp;
				counter_g++;

				file >> tmp;

				if (tmp[0] != 'a')
					file >> tmp;

				tmp = tmp.erase(0, 7);

				amount = atoi(tmp.c_str());

				amount_g += amount;
			}
		}
	}
}

int main()
{
	clock_t start_time = clock();
	{
		int counter = 0;
		{
			ifstream file1("order.0.0");
			counter += count(file1);
			ifstream file2("order.0.3");
			counter += count(file2);
			ifstream file3("order.1.1");
			counter += count(file3);
			ifstream file4("order.2.2");
			counter += count(file4);

			file1.close();
			file2.close();
			file3.close();
			file4.close();
		}
		
		cout << counter << endl;
	}

	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << endl;

    start_time = clock();
	{
		string orderid_toget;
		cin >> orderid_toget;

		ifstream file1("order.0.0");
		ifstream file2("order.0.3");
		ifstream file3("order.1.1");
		ifstream file4("order.2.2");
		if (!findorder(orderid_toget, file1))
			if (!findorder(orderid_toget, file2))
				if (!findorder(orderid_toget, file3))
					if (!findorder(orderid_toget, file4))
						cout << "Not found" << endl;

		file1.close();
		file2.close();
		file3.close();
		file4.close();
	}
	end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << endl;


	start_time = clock();
	{
		string buyerid_toget;
		cin >> buyerid_toget;

		ifstream buyer1("buyer.0.0");
		ifstream buyer2("buyer.1.1");

		if (!findbuyer(buyerid_toget, buyer1))
			if (!findbuyer(buyerid_toget, buyer2))
				cout << "Not found" << endl;

		buyer1.close();
		buyer2.close();

		ifstream file1("order.0.0");
		ifstream file2("order.0.3");
		ifstream file3("order.1.1");
		ifstream file4("order.2.2");
		findorder_b(buyerid_toget, file1);
		findorder_b(buyerid_toget, file2);
		findorder_b(buyerid_toget, file3);
		findorder_b(buyerid_toget, file4);

		file1.close();
		file2.close();
		file3.close();
		file4.close();

		cout << counter_b << endl;
		cout << amount_b << endl;
	}
	end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << endl;

	start_time = clock();
	{
		string goodid_toget;
		cin >> goodid_toget;

		ifstream good1("good.0.0");
		ifstream good2("good.1.1");
		ifstream good3("good.2.2");

		if (!findgood(goodid_toget, good1))
			if (!findgood(goodid_toget, good2))
				if (!findgood(goodid_toget, good3))
					cout << "Not found" << endl;
		

		good1.close();
		good2.close();
		good3.close();

		ifstream file1("order.0.0");
		ifstream file2("order.0.3");
		ifstream file3("order.1.1");
		ifstream file4("order.2.2");
		findorder_g(goodid_toget, file1);
		findorder_g(goodid_toget, file2);
		findorder_g(goodid_toget, file3);
		findorder_g(goodid_toget, file4);

		file1.close();
		file2.close();
		file3.close();
		file4.close();

		cout << counter_g << endl;
		cout << amount_g << endl;
	}
	end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	return 0;
}