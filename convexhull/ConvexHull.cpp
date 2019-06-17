#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
//#include <windows.h>

using namespace std;
using namespace cv;

#define e 3.3621e-4932
Point2f pmin;

//判断点C P是否在AB直线同侧
bool SameSide(Point2f A, Point2f B, Point2f C, Point2f P)
{
	long double k = (long double)(A.y - B.y) / (A.x - B.x);
	long double b = A.y - k * A.x;
	if ((C.y - k * C.x - b >= e && P.y - k * P.x - b >= e) || (C.y - k * C.x - b <= e && P.y - k * P.x - b <= e))
		return true;
	else
		return false;
}
//判断P是否在ABC点构成的三角形内
bool PointinTriangle1(Point2f A, Point2f B, Point2f C, Point2f P)
{
	return SameSide(A, B, C, P) && SameSide(B, C, A, P) && SameSide(C, A, B, P);
}

bool cmpBy_yr(Point2f a, Point2f b)
{
	return a.y < b.y;
}


bool cmpBy_yl(Point2f a, Point2f b)
{
	return a.y > b.y;
}

bool cmpBy_x(Point2f a, Point2f b)
{
	return a.x < b.x;
}
//通过向量内积比较两点与基点连线角度
inline bool cmpBy_ang(const Point2f pt1, const Point2f &pt2)
{
	float m1 = sqrt((float)(pt1.x * pt1.x + pt1.y * pt1.y));
	float m2 = sqrt((float)(pt2.x * pt2.x + pt2.y * pt2.y));
	float v1 = (pt1.x - pmin.x) * (pt2.y - pmin.y) - (pt1.y - pmin.y) * (pt2.x - pmin.x);
	return (v1 > 0 || (v1 == 0 && m1 < m2));
}

void drawLine(vector<Point2f> points, vector<Point2f> p)
{
	vector<Point2f> left, right;
	int num = p.size();
	int miny_index = 0, maxy_index = 0;

	float k, b;

	Mat Draw_Convex_Hull(600, 600, CV_8UC3, Scalar(200, 200, 200));

	for (int i = 0; i < points.size(); i++)
	{
		circle(Draw_Convex_Hull, points[i], 1, Scalar(0, 0, 0), 1);
	}

	for (int i = 0; i < num; i++)
	{
		if (p[i].y < p[miny_index].y)
			miny_index = i;
		if (p[i].y > p[maxy_index].y)
			maxy_index = i;
	}

	k = (p[maxy_index].y - p[miny_index].y) / (p[maxy_index].x - p[miny_index].x);
	b = p[maxy_index].y - k * p[maxy_index].x;
	for (int i = 0; i < num; i++)
	{
		if (p[i].y - k * p[i].x - b > 0)
		{
			left.push_back(p[i]);
		}
		else
		{
			right.push_back(p[i]);
		}
	}
	sort(right.begin(), right.end(), cmpBy_yr);
	sort(left.begin(), left.end(), cmpBy_yl);
	for (int i = 0; i < right.size() - 1; i++)
	{
		line(Draw_Convex_Hull, right[i], right[i + 1], Scalar(0, 255, 0), 4);
		waitKey(30);
	}
	for (int i = 0; i < left.size() - 1; i++)
	{
		line(Draw_Convex_Hull, left[i], left[i + 1], Scalar(0, 255, 0), 4);
		waitKey(30);
	}
	line(Draw_Convex_Hull, right[right.size() - 1], left[0], Scalar(0, 255, 0), 4);
	line(Draw_Convex_Hull, left[left.size() - 1], right[0], Scalar(0, 255, 0), 4);
	imshow("Convex Hull", Draw_Convex_Hull);
	waitKey(0);
}
//暴力搜素方法
void bruteForce(vector<Point2f> &p, vector<Point2f> &vec)
{

	int num = p.size();
	int min_index = 0;
	Point2f min = p[0], tmp;
	vector<bool> flag(num, true);

	for (int i = 1; i < num; i++)
	{
		if ((p[i].y < min.y) || (p[i].y == min.y && p[i].x < min.x))
		{
			min = p[i];
			min_index = i;
		}
	}
	tmp = p[0];
	p[0] = min;
	p[min_index] = tmp;
	vec.push_back(p[0]);
	for (int i = 1; i < num; i++)
		for (int j = 0; j < num; j++)
			for (int k = j + 1; k < num; k++)
			{
				if (i != j && i != k)
					if (PointinTriangle1(p[j], p[k], p[0], p[i]))
						flag[i] = false;
			}
	for (int i = 1; i < num; i++)
	{
		if (flag[i])
			vec.push_back(p[i]);
	}
}

void grahamScan(vector<Point2f> &p, vector<Point2f> &vec)
{


	vector<Point2f> ang;

	int num = p.size();
	int min_index = 0;
	Point2f min = p[0], tmp, top1, top;
	vector<bool> flag(num, true);

	for (int i = 1; i < num; i++)
	{
		if ((p[i].y < min.y) || (p[i].y == min.y && p[i].x < min.x))
		{
			min = p[i];
			min_index = i;
		}
	}
	tmp = p[0];
	p[0] = min;
	pmin = min;
	p[min_index] = tmp;
	vec.push_back(p[0]);
	sort(p.begin() + 1, p.end(), cmpBy_ang);
	vec.push_back(p[1]);
	vec.push_back(p[2]);
	for (int i = 3; i < num; i++)
	{
		while (PointinTriangle1(p[i], vec[vec.size() - 2], p[0], vec[vec.size() - 1]) && vec.size() > 2)
			vec.pop_back();
		vec.push_back(p[i]);
	}
}

void Divide_Conquer(vector<Point2f> &p, int l, int r, vector<Point2f> &vec)
{
	if (r - l < 3)
		return;
	if (r - l == 3)
	{
		vec.insert(vec.end(), p.begin() + l, p.begin() + r + 1);
		return;
	}

	double countx = 0;
	for (int i = l; i <= r; i++)
		countx += p[i].x;
	countx /= (r - l + 1);
	int k = (l + r) / 2;

	vector<Point2f> temp_left, temp_right, answer;
	Divide_Conquer(p, k + 1, r, temp_right);
	Divide_Conquer(p, l, k, temp_left);
	temp_left.insert(temp_left.end(), temp_right.begin(), temp_right.end());
	grahamScan(p, answer);
	vec.insert(vec.end(), answer.begin(), answer.end());
}


void Divide_Conquer_Warp(vector<Point2f> &p, vector<Point2f> &vec)
{
	sort(p.begin(), p.end(), cmpBy_x);
	Divide_Conquer(p, 0, p.size() - 1, vec);

}

int main()
{
	float x, y;
	int num = 180;
	vector<Point2f> vp2f;
	vector<Point2f> con_hull;

	//LARGE_INTEGER t1, t2, tc;
	//QueryPerformanceFrequency(&tc);

	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		x = rand()*1. / (RAND_MAX / 500.);
		y = rand()*1. / (RAND_MAX / 500.);
		vp2f.push_back(Point2f(x, y));
	}


	//通过频率获取程序执行时间
	//QueryPerformanceCounter(&t1);
	grahamScan(vp2f, con_hull);
	//QueryPerformanceCounter(&t2);
	//cout << "Point Numbers: " << num << "\t" << "Time of Graham_Scan： " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	cout<<"point numbers:"<<num<<endl;
	drawLine(vp2f, con_hull);


	return 0;
}
