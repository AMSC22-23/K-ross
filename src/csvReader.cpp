//@note: use compile flags and include only "csvReader.hpp"
#include "../include/csvReader.hpp"

    CSVReader::CSVReader(const std::string &filename) : filename(filename) {}
    std::vector<Point> CSVReader::readData()
    {
        std::vector<Point> points;

        // Open the CSV file
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            return points;
        }

        // Read the file line by line
        std::string line;
        while (getline(file, line))
        {
            // Create a std::stringstream from the line
            std::stringstream ss(line);

            // Parse the CSV values
            std::string id_str, f1_str, f2_str, name;
            getline(ss, id_str, ',');
            getline(ss, f1_str, ',');
            getline(ss, f2_str, ',');
            getline(ss, name, ',');

            // Convert std::strings to appropriate types
            //@note: explicitly use std namespace
            int id = stoi(id_str);
            double f1 = stod(f1_str);
            double f2 = stod(f2_str);

            // Create a point and add it to the std::vector
            //@note: could have been nice to use emplace back here
            points.push_back(Point(id - 1, f1, f2));
        }

        return points;
    }
