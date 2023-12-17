#ifndef POINTS_VECT_HPP
#define POINTS_VECT_HPP

#include <iostream>
#include <vector>

#include "point.hpp"

using namespace std;

class Points_vect
{
private:
    vector<Point> points;
    int number_of_points = 0;
    string name;

public:
    Points_vect();//default constructor
    int getNumberOfPoints();
    void addPoint(Point point);
    void removePoint(int id_point);
    Point& getPoint(int index); 

    // only for ginuplot
    vector<vector<double>> getPointsCoordinates();
};

#endif

