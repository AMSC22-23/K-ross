#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

class Point
{
public:
    int id;
    double x, y;
    int clusterId;
    // double minDist;

    Point();
    Point(int id, double x, double y);
    double distance(Point p);
};


#endif // POINT_HPP