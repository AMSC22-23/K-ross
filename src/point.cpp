//@note: use compile flags and include only "point.hpp"
#include "../include/point.hpp"

Point::Point() : id(0), x(0.0), y(0.0), clusterId(-1) /*,minDist(std::numeric_limits<double>::max())*/ {}

Point::Point(int id, double x, double y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}

//@note: should pass by const reference
double Point::distance(Point p)
{
		//@note: pow with integer exponent should not use pow
		//       also should explitictly use std:: math functions
    return sqrt(pow(x - p.x, 2.0) + pow(y - p.y, 2.0));
}
