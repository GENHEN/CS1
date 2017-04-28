/*
File Name: hw3.cpp
Author: genhen
Date Created: 04/08/2014
Run: g++ -std=c++14 -o hw3.exe hw3.cpp && ./hw3.exe && rm hw3.exe
Description: Uses three classes that are inherited from one another Point2D,
             WeightedPoint2D, and ColorPoint2D. Uses polymorphisms to
             display the points.
*/

#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

/** @class Point2D
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
        double getx();
        double gety();
        void print();
        string print_string();

        // Mutators
        void setx(double x_new);
        void sety(double y_new);

    private:
        double x_cord, y_cord;
};

/** @class ColorPoint2D
    @brief Class for (x,y) points with a color string

    This class is designed to store and modify points in the plane. It inherits from
    and has the properties of the Point2D class. However, it has a string clss that
    stores the color of the point as well that is to be displayed in the print function
*/
class ColorPoint2D : public Point2D
{
    public:
        // Constructors
        ColorPoint2D();
        ColorPoint2D(double x, double y, string col);

        // Accessors
        string getcolor();
        void print();
        string print_string();

        // Mutators
        void setcolor(string col);

    private:
        string color;
};

/** @class WeightedPoint2D
    @brief Class for (x,y) points with a color string and a weight value

    This class is designed to store and modify points in the plane. It inherits from
    and has the properties of the ColorPoint2D function, except it has a weight
    value as well
*/
class WeightedPoint2D : public Point2D
{
    public:
        //Constructors
        WeightedPoint2D();
        WeightedPoint2D(double x, double y, double weight_input);

        // Accessors
        double getweight();
        void print();
        string print_string();

    private:
        double weight;
};


int main()
{
    int user_point_selection = 0;
    string result = "";

    cout << "Welcome to Point Printer! You can create three different kinds of points:" << endl
         << endl
         << "1. Point2D, e.g., (2,6.5)"              << endl
         << "2. ColorPoint2D, e.g., blue(-4.5,3.5)"  << endl
         << "3. WeightedPoint2D, e.g., .12(3.6,8.7)" << endl
         << endl
         << "Enter 0 when you are finished."         << endl << endl;

    
    double x_cord, y_cord;
    int counter = 1;

    do
    {
        cout << "Selection: ";
        cin >> user_point_selection;

        if(user_point_selection == 1 || user_point_selection == 2 ||
           user_point_selection == 3)
        {
            cout << "x = ";
            cin >> x_cord;
            cin.ignore();

            cout << "y = ";
            cin >> y_cord;
            cin.ignore();

            result += to_string(counter++) + ": ";
        }

        if(user_point_selection == 1)
        {
            Point2D point_in_2D(x_cord, y_cord);
            result += point_in_2D.print_string() + "\n";
        }
        else if(user_point_selection == 2)
        {
            string color;

            cout << "color = ";
            getline(std::cin, color);

            ColorPoint2D color_point(x_cord, y_cord, color);
            result += color_point.print_string() + "\n";
        }
        else if(user_point_selection == 3)
        {
            double weight = 0.0;

            cout << "weight = ";
            cin >> weight;
            cin.ignore();

            WeightedPoint2D weighted_point(x_cord, y_cord, weight);
            result += weighted_point.print_string() + "\n";
        }
    } while(user_point_selection != 0);

    cout << endl << "Your points are" << endl
         << endl
         << result << endl;

	return 0;
}

//
//      POINT2D CLASS CONSTRUCTORS
//
/**
	Creates default point at origin, (0,0)
*/
Point2D::Point2D() : x_cord(0), y_cord(0)
{ }

/**
	Creates a Point2D instance using inputs into contructor

	@param x is the x coordinate in the Point2D
	@param y is the y coordinate in the Point2D
*/
Point2D::Point2D(double x, double y) : x_cord(x), y_cord(y)
{ }

//
//      POINT2D ACCESSORS
//
/**
	Returns x coordinate 

	@return private member variable x_coord
*/
double Point2D::getx()
{
    return x_cord;
}

/**
    Returns y coordinate

    @return private member variable x_coord
*/
double Point2D::gety()
{
    return y_cord;
}

/**
	Prints x and y coordinates in (x,y) form
*/
void Point2D::print()
{
	cout << '(' << x_cord << ", " << y_cord << ')';
	return;
}

/**
    @return the printed form of Point2D object
*/
string Point2D::print_string()
{
    string x_string = to_string(x_cord),
           y_string = to_string(y_cord);

    while(x_string.back() == '0')
        x_string.pop_back();
    while(y_string.back() == '0')
        y_string.pop_back();

    if(x_string.back() == '.')
        x_string.pop_back();
    if(y_string.back() == '.')
        y_string.pop_back();

    return ("(" + x_string + ", " + y_string + ")");
}

//
//      POINT2D MUTATORS
//
/**
	Sets x floating point value to a new value

	@param x_new is the newer value to assign
*/
void Point2D::setx(double x_new)
{
    x_cord = x_new;
    return;
}

/**
    Sets y floating point value to a new value

    @param y_new is the newer value to assign
*/
void Point2D::sety(double y_new)
{
    y_cord = y_new;
    return;
}

//
//      COLORPOINT2D CLASS CONSTRUCTORS
//
/**
	Defaults color to empty string
*/
ColorPoint2D::ColorPoint2D() : color("")
{ }

/**
    Contructs ColorPoint2D based off of given x,y coords and color

	@param a the x-coordinate
	@param b the y-coordinate
	@param col the color
*/
ColorPoint2D::ColorPoint2D(double x, double y, string col) : Point2D(x,y), color(col)
{ }

//
//      COLORPOINT2D ACCESSORS
//
/**
	@return returns the color of the object.
*/
string ColorPoint2D::getcolor()
{
    return color;
}

/**
	Prints ColorPoint2D in color(x,y) format
*/
void ColorPoint2D::print()
{
	cout << color;
	Point2D::print();
	return;
}

/**
    @return the printed form of ColorPoint2D object
*/
string ColorPoint2D::print_string()
{
    return (color + Point2D::print_string());
}

//
//      COLORPOINT2D MUTATORS
//
/**
	Sets the value of color using input value in col

	@param col is the input string value
*/
void ColorPoint2D::setcolor(string col)
{
    color = col;
    return;
}

//
//      WEIGHTEDPOINT2D CONSTRUCTORS
//
/**
	Sets the value of weight using default weight of 0.0
*/
WeightedPoint2D::WeightedPoint2D()
{
    weight = 0.0;
}

/**
	Using contructor parameters to fill WeightedPoint2D object
*/
WeightedPoint2D::WeightedPoint2D(double x, double y, double weight_input) : Point2D(x,y), weight(weight_input)
{ }

//
//      WEIGHTEDPOINT2D ACCESSORS
//
/**
	@return 'weight' floating point value of this object
*/
double WeightedPoint2D::getweight()
{
    return weight;
}

/**
	Prints WeightedPoint2D object
*/
void WeightedPoint2D::print()
{
    cout << weight;
    Point2D::print();
}

/**
    @return the printed form of WeightedPoint2D object
*/
string WeightedPoint2D::print_string()
{
    string weight_string = to_string(weight);

    while(weight_string.back() == '0')
        weight_string.pop_back();

    if(weight_string.back() == '.')
        weight_string.pop_back();

    return (weight_string + Point2D::print_string());
}
