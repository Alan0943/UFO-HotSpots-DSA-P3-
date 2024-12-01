#include "UFO_Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cmath>


UFO::UFO() {
    // data set
    filesystem::path filepath = "../resources/ufo_sightings.csv";
    
    // opens file
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
    }

    string line;
    int lat,lon;
    bool isHeader = true;

    // inputs file data into grid_map
    while (getline(file, line)) {

        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        Row data;
        string field;

        // Read each field based on column headers
        getline(ss, data.city, ',');
        getline(ss, data.state, ',');
        getline(ss, data.country, ',');

        getline(ss, data.shape, ',');
        getline(ss, data.duration, ',');
        getline(ss, data.description, ',');

        // removes commas so lat/long can be converted to double
        getline(ss, field, ',');
        data.latitude = stod(field);
        getline(ss, field, ',');
        data.longitude = stod(field);

        getline(ss, data.year, ',');
        getline(ss, data.month, ',');
        getline(ss, data.day, ',');
        getline(ss, data.hour, ',');
        getline(ss, data.minute, ',');

        getline(ss, data.year_doc, ',');
        getline(ss, data.month_doc, ',');
        getline(ss, data.day_doc, ',');

        // gets key value, which is lat,lon of lower left corner of grid
        // does this by dividing lat/lon by 10, flooring it, then * 10
        lat = int(floor(data.latitude / 10)) * 10;
        lon = int(floor(data.longitude / 10)) * 10;

        grid_map[{lat, lon}].push_back(data);

    }
}

// inserts new data
void UFO::insert(double lat, double lon, vector<string> vec) {

    int new_lat = int(floor(lat / 10)) * 10;
    int new_lon = int(floor(lon / 10)) * 10;

    // error checks to see if coords are out of bounds
    if (new_lat > 50 || new_lat < 30 || new_lon < -120 || new_lon > -60) {
        cout << "Invalid Coordinates";
        return;
    }

    Row data;

    data.city = vec[0];
    data.state = vec[1];
    data.country = vec[2];

    data.shape = vec[3];
    data.duration = vec[4];
    data.description = vec[5];

    data.latitude = lat;
    data.longitude = lon;

    data.year = vec[8];
    data.month = vec[9];
    data.day = vec[10];
    data.hour = vec[11];
    data.minute = vec[12];

    data.year_doc = vec[13];
    data.month_doc = vec[14];
    data.day_doc = vec[15];

    grid_map[pair(new_lat,new_lon)].push_back(data);

}

vector<UFO::Row> UFO::sortHelper(double lat, double lon, int radius, string dataType) {
    vector<Row> result;
    return result;
}

// need to implement
vector<UFO::Row> UFO::mergeSort(vector<UFO::Row> vec) {

}

// need to implement
vector<UFO::Row> UFO::quickSort(vector<UFO::Row> vec) {

}

