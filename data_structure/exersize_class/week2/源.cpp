#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Point
{
public:
	double x;
	double y;
};

struct Line
{
	double k;
	double b;
};

int judge(vector<Point> point)
{
	int length = point.size();

	for (int i = 0; i < length; i++)
	{
		double cross = (point[(i + 2) % length].x - point[i].x)*(point[(i + 1) % length].y - point[i].y) - (point[(i + 2) % length].y - point[i].y)*(point[(i + 1) % length].x - point[i].x);
		if (cross < 0)
			return i;
	}

	return -1;
}

void getLine(double x1, double y1, double x2, double y2, Line &line)
{
	double m = 0;

	m = x2 - x1;

	if (0 == m)
	{
		line.k = 10000.0;
		line.b = y1 - line.k * x1;
	}
	else
	{
		line.k = (y2 - y1) / (x2 - x1);
		line.b = y1 - line.k * x1;
	}
}

void split(vector<Point> point, int i)
{
	Point tmp;
	double mindistance = 99999;
	int length = point.size();
	int crosslastindex;
	Line line1, line2;
	Point cross;
	getLine(point[i % length].x, point[i% length].y, point[(i + 1) % length].x, point[(i + 1) % length].y, line1);
	
	for (int j = 2; j < length - 1; j++)
	{
		Point pt;
		getLine(point[(i+j) % length].x, point[(i+j)% length].y, point[(i+j + 1) % length].x, point[(i+j + 1) % length].y, line2);

		if ((line1.k - line2.k) > 0.2 || (line1.k - line2.k) < -0.2)
		{
			double tmp;
			pt.x = (line2.b - line1.b) / (line1.k - line2.k);
			pt.y = line1.k * pt.x + line1.b;
			tmp = (point[(i+1)%length].x - pt.x)*(point[(i + 1) % length].x - pt.x)+ (point[(i + 1) % length].y - pt.y)*(point[(i + 1) % length].y - pt.y);
			int xxx=point[(i + j) % length].x;
			int yyy=point[(i + j+1) % length].x;
			if (((pt.x >= point[(i + j) % length].x - 0.1) && (pt.x <= point[(i + j+1) % length].x + 0.1)) || ((pt.x <= point[(i + j) % length].x + 0.1) && (pt.x >= point[(i + j + 1) % length].x - 0.1)))
			{
				if (abs(pt.x- point[(i+1) % length].x) <= abs(pt.x - point[(i) % length].x))
				{
					if (mindistance > tmp && tmp > 0.1) {
						mindistance = tmp;
						cross.x = pt.x;
						cross.y = pt.y;
						crosslastindex = (i + j) % length;
					}
				}
			}
		}
	}

	vector<Point> polygon1;
	vector<Point> polygon2;
	for (int j = (i + 1)%length; j <= crosslastindex; j++)
	{
		tmp.x = point[j].x;
		tmp.y = point[j].y;

		if (j > crosslastindex + 1 && abs(tmp.x - cross.x) < 0.1 && abs(tmp.x - point[(j - 1) % length].x) < 0.1)
			continue;
		if (j > crosslastindex + 1 && abs(tmp.x - polygon1[polygon1.size() - 1].x) < 0.1 && abs(tmp.y - polygon1[polygon1.size() - 1].y) < 0.1)
			continue;
		polygon1.push_back(tmp);
	}

	tmp.x = cross.x;
	tmp.y = cross.y;
	polygon1.push_back(tmp);
	polygon2.push_back(tmp);

	for (int j = crosslastindex+1; j%length != (i+1)%length + 1; j++)
	{
		tmp.x = point[j%length].x;
		tmp.y = point[j%length].y;
		if ((j%length == (i + 1) % length) && abs(tmp.x - cross.x) < 0.1 && abs(tmp.y - cross.y))
			continue;
		if (j > crosslastindex + 1 && abs(tmp.x - cross.x) < 0.1 && abs(tmp.x - point[(j - 1) % length].x) < 0.1)
			continue;
		if (j > crosslastindex + 1 && abs(tmp.x - polygon2[polygon2.size()-1].x) < 0.1 && abs(tmp.y - polygon2[polygon2.size() - 1].y) < 0.1)
			continue;
		polygon2.push_back(tmp); 
	}

	int index1 = judge(polygon1);
	int index2 = judge(polygon2);
	if (index1 < 0)
	{
		for (int i = 0; i < polygon1.size(); i++)
		{
			cout << polygon1[i].x << ' ' << polygon1[i].y << '\t';
		}
		cout << endl;
	}
	else
		split(polygon1, index1);

	
	if (index2 < 0)
	{
		for (int i = 0; i < polygon2.size(); i++)
		{
			cout << polygon2[i].x << ' ' << polygon2[i].y << '\t';
		}
		cout << endl;
	}
	else
		split(polygon2, index2);
}

int main()
{
	vector<Point> point;
	double x;
	double y;
	int length;
	bool flag = true;

	while (cin >> x && cin >> y)
	{
		Point tmp;
		tmp.x = x;
		tmp.y = y;
		point.push_back(tmp);
	}

	length = point.size();

	for (int i = 0; i < length; i++)
	{
		double cross = (point[(i+2)% length].x - point[i].x)*(point[(i+1) % length].y - point[i].y) - (point[(i+2)% length].y - point[i].y)*(point[(i+1) % length].x - point[i].x);
		if (cross < 0)
		{
			flag = false;
			split(point, i);
			break;
		}						
	}

	if (flag)
		cout << "convex" << endl;
	else
		cout << "concave" << endl;
	return 0;
}