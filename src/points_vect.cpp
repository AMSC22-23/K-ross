#include "points_vect.hpp"

Points_vect::Points_vect() = default; //default constructor

int Points_vect::getNumberOfPoints()
{
    return number_of_points;
};

void Points_vect::addPoint(Point point){
    points.push_back(point);
    number_of_points++;
};

void Points_vect::removePoint(int id_point)
{
    int num = points.size();
    for(int i = 0; i < num; i++)
    {
        if(points[i].getID() == id_point)
        {
            points.erase(points.begin() + i);
            number_of_points--;
            return;
        }
    }
}; 

// only for ginuplot
vector<vector<double>> Points_vect::getPointsCoordinates(){
    vector<vector<double>> points_coordinates;
    for(int i = 0; i < number_of_points; i++)
    {
        vector<double> point_coordinates;
        for(int j = 0; j < points.at(i).getNumberOfFeatures(); j++)
            point_coordinates.push_back(points.at(i).getValue(j));
        points_coordinates.push_back(point_coordinates);
    }
    return points_coordinates;
};

Point& Points_vect::getPoint(int index){
    return points.at(index);
};



