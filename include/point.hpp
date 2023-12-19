#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

//@note: could have been nice if the point was n dimensional
class Point
{
public:
    int id;
    double x, y;
    int clusterId;
    // double minDist;

    Point();
    Point(int id, double x, double y);
    //@note: const method
    double distance(Point p);
};


#endif // POINT_HPP