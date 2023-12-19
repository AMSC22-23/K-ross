#include "../include/point.hpp"

Point::Point() : id(0), x(0.0), y(0.0), clusterId(-1) /*,minDist(std::numeric_limits<double>::max())*/ {}

Point::Point(const int& id, const double& x, const double& y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}

double Point::distance(const Point& p) const
{
    return sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
}

double& Point::getX() 
{
    return x;
}

double& Point::getY() 
{
    return y;
}

void Point::setX( double x)
{
    this->x = x;
}

void Point::setY( double y)
{
    this->y = y;
}
