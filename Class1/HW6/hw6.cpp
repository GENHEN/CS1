/*
File Name: hw6.cpp
Author: genhen
Description: Takes a bunch of points and stores them as Point2D class objects
             and then reorders them by their respective distance to the origin
             then by how much of an angle they have to the x-axis.
Run: g++ -std=c++14 -o hw6.exe hw6.cpp && ./hw6.exe && rm hw6.exe
*/

#include <algorithm>
//#include <cctype>
#include <cmath>
//#include <conio.h>
//#include <cstring>
//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <ctype.h>
#include <fstream>
//#include <iomanip>
#include <iostream>
//#include <limits>
#include <math.h>
#include <vector>
//#include <windows.h>

using namespace std;

const double PI = 3.14159265358979323846264338327950;

/**
	@class Point2D
	@brief Class for (x,y) points

	This class is designed to store and modify points in the plane.  You can print
	out the coordinates or move the points or transform them however you like.  The
	coordinates are stored as two private variables x and y representing the x- and y-
	coordinates in a point (x,y).
*/
class Point2D
{
	public:
		// Constructors
		Point2D();
		Point2D(double x, double y);

		// Accessors
		double getx() const;
		double gety() const;
		double get_distance_from_origin() const;
		double get_angle_from_origin() const;
		void print() const;

	private:
		double x_cord,
		       y_cord,
		       angle_from_origin,
		       distance_from_origin;
};

bool operator<(const Point2D &pt1, const Point2D &pt2);

int main()
{
	//
	// Complexity: O(n*log(n))
	//
	double x, y;
	vector<Point2D> points_from_user; //= { Point2D(1,2), Point2D(2,3), Point2D(1.1,2.2), Point2D(-10,10), Point2D(-5,-3), Point2D(-5,3), Point2D(5,-3), Point2D(5,3) }; // DEBUG TEST SET OF POINTS
	Point2D *temp_2d_point;

	cout << "Welcome to Point Printer! Please insert the x-and y-coordinates for your"     << endl
	     << "points and I will print them in sorted order by distance! Just one rule, the" << endl
	     << "point (0,0) is reserved as the terminating point, so when you are done "      << endl
	     << "enter (0,0)."                                                                 << endl;

	while(true)
	{
		cout << "x = ";
		cin >> x;
		cout << "y = ";
		cin >> y;

		if(x != 0.0  &&  y != 0.0)
		{
			temp_2d_point = new Point2D(x, y);
			points_from_user.push_back(*temp_2d_point);
			delete temp_2d_point;
		}
		else
			break;
	}

	sort(points_from_user.begin(), points_from_user.end());
	cout << endl << "Your points in sorted order are:";
	for(int counter = 0, len = points_from_user.size(); counter < len; counter++)
	{
		cout << endl << (counter + 1) << ": ";
		points_from_user[counter].print();
	}
	cout << endl;

	return 0;
}

//
//      POINT2D CLASS CONSTRUCTORS
//
/**
	Creates default point at origin, (0,0)
*/
Point2D::Point2D() : x_cord(0.0), y_cord(0.0), distance_from_origin(0.0)
{  }

/**
	Creates a Point2D instance using inputs into contructor

	@param x is the x coordinate in the Point2D
	@param y is the y coordinate in the Point2D
*/
Point2D::Point2D(double x, double y) : x_cord(x), y_cord(y),
                                       distance_from_origin(sqrt((x*x) + (y*y))),
                                       angle_from_origin(atan2(y,x))
{
	if(angle_from_origin < 0)
		angle_from_origin += (PI + PI);
}

//
//      POINT2D ACCESSORS
//
/**
	Returns x coordinate

	@return private member variable x_coord
*/
double Point2D::getx() const
{
	return x_cord;
}

/**
	Returns y coordinate

	@return private member variable x_coord
*/
double Point2D::gety() const
{
	return y_cord;
}

/**
	Prints x and y coordinates in (x,y) form
*/
void Point2D::print() const
{
	cout << '(' << x_cord << ',' << y_cord << ')';
	return;
}

/**
	@return Returns the distance from the origin that was already stored in the
	        private variable 'distance_from_origin'
*/
double Point2D::get_distance_from_origin() const
{
	return distance_from_origin;
}

/**
	@return the angle between 0-2π radians
*/
double Point2D::get_angle_from_origin() const
{
	return angle_from_origin;
}

//
//      POINT2D OPERATOR FUNCTIONS
//
/**
	Compares if Point2D on left is less than Point2D on right
	using distance_from_origin first, and if same distance_from_origin,
	then compares angle_from_origin
*/
bool operator<(const Point2D &pt1, const Point2D &pt2)
{
	if(pt1.get_distance_from_origin() < pt2.get_distance_from_origin())
		return true;
	else if(pt1.get_distance_from_origin() > pt2.get_distance_from_origin())
		return false;
	else
		return (pt1.get_angle_from_origin() < pt2.get_angle_from_origin());
}
