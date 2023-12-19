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
    Point(const int& id, const double& x, const double& y);
    double distance(const Point& p) const;

    double& getX() ;
    double& getY() ;
    void setX(double x);
    void setY(double y);
};


#endif // POINT_HPP