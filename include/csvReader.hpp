#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "point.hpp"

//@note: nothing wrong with this being a class, but a free function would have had the 
//       same semantics without the necessity of a class
//@note: could be nice if could read CSV with arbitrary number of columns
class CSVReader
{
public:
    CSVReader(const std::string &filename);
    std::vector<Point> readData();

private:
    std::string filename;
};


#endif // CSVREADER_HPP