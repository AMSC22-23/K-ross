#include "../include/point.hpp"

Point::Point() : id(0), x(0.0), y(0.0), clusterId(-1) /*,minDist(std::numeric_limits<double>::max())*/ {}

Point::Point(int id, double x, double y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}

double Point::distance(Point p)
{
    return sqrt(pow(x - p.x, 2.0) + pow(y - p.y, 2.0));
}
