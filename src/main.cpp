#include <iostream>
#include <fstream>
#include <sstream>
#include "UFO_Data.h"
#include <vector>
#include <string>
using namespace std;


int main() {

    ifstream file("ufo_sightings.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // use for testing csv reading
//    string line;
//    bool isHeader = true;
//    int lineCount = 0;
//
//    while (getline(file, line)) {
//        if (isHeader) {
//            isHeader = false;
//            continue;
//        }
//
//        lineCount++;
//        if (lineCount >= 50) {
//            break;
//        }
//    }
//
//    file.close();


    vector<UFO> ufoList;
    string line;
    bool isHeader = true;

    while (getline(file, line)) {

        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        UFO ufo;
        string field;

        // Read each field based on column headers
        getline(ss, ufo.city, ',');
        getline(ss, ufo.state, ',');
        getline(ss, ufo.country, ',');

        getline(ss, ufo.shape, ',');
        getline(ss, ufo.duration, ',');
        getline(ss, ufo.description, ',');

        // removes commas so lat/long can be converted to double
        getline(ss, field, ',');
        ufo.latitude = stod(field);
        getline(ss, field, ',');
        ufo.longitude = stod(field);

        getline(ss, ufo.year, ',');
        getline(ss, ufo.month, ',');
        getline(ss, ufo.day, ',');
        getline(ss, ufo.hour, ',');
        getline(ss, ufo.minute, ',');

        getline(ss, ufo.year_doc, ',');
        getline(ss, ufo.month_doc, ',');
        getline(ss, ufo.day_doc, ',');

        ufoList.push_back(ufo);
    }

    cout << ufoList[60090].longitude << endl;

    // Testing



}


