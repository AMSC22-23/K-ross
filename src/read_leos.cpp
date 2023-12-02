/*

This is just en easier example that I started from to implement the other.

Main difference is that here we use a lot sstream which is more straightforward for simple cases,
but is not ok for csv containing empty spaces, commas inside strings, etc ...

*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "read_leos.hpp"


using namespace std;


int read_leos(vector<Entry>& data) {
    // Open the CSV file
    ifstream file("./Files/profiling.csv");

    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    // Define vectors to store entries
    vector<Entry> entries;

    // Read the file line by line
    string line;
    while (getline(file, line)) {
        // Create a stringstream from the line
        stringstream ss(line);

        // Parse the CSV values
        string id_str, f1_str, f2_str, name;
        getline(ss, id_str, ',');
        getline(ss, f1_str, ',');
        getline(ss, f2_str, ',');
        getline(ss, name, ',');

        // Convert strings to appropriate types
        int id = stoi(id_str);
        double f1 = stod(f1_str);
        double f2 = stod(f2_str);

        // Create an entry and add it to the vector
        entries.push_back({id, f1, f2, name});
    }

    // Display the entries (optional)
    /*
    cout << "ID\tF1\tF2\tName\n";
    for (const auto& entry : entries) {
        cout << entry.id << "\t" << entry.f1 << "\t" << entry.f2 << "\t" << entry.name << endl;
    }
    */

    data = entries;

    return 0;
}
