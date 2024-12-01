#include "UFO_Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>


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

// https://www.geeksforgeeks.org/haversine-formula-to-find-distance-between-two-points-on-a-sphere/
double UFO::distanceCalc(double lat1, double lon1, double lat2, double lon2) {

    // finds distance between lats/lons
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply haversine formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    // mean radius in terms of miles
    double rad = 3959.0;

    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<UFO::Row> UFO::sortHelper(double lat, double lon, int radius) {

    // Determine the key of the current grid
    int lat_key = int(floor(lat / 10)) * 10;
    int lon_key = int(floor(lon / 10)) * 10;

    vector<Row> result;
    double current_dist;

    // List of all grid keys to check (current grid + adjacent grids)
    vector<pair<int, int>> grids_to_check = {
            {lat_key, lon_key},                 // current grid
            {lat_key - 10, lon_key},            // north
            {lat_key + 10, lon_key},            // south
            {lat_key, lon_key - 10},            // west
            {lat_key, lon_key + 10},            // east
            {lat_key - 10, lon_key - 10},       // north-west
            {lat_key - 10, lon_key + 10},       // north-east
            {lat_key + 10, lon_key - 10},       // south-west
            {lat_key + 10, lon_key + 10}        // south-east
    };

    // Loop through each grid to check
    for (const auto& grid : grids_to_check) {

        // Check if the grid exists in the map
        if (grid_map.find(grid) != grid_map.end()) {

            for ( auto& i : grid_map[grid]) {

                // Calculate the distance between the current location and the sighting
                current_dist = distanceCalc(lat, lon, i.latitude, i.longitude);

                // If the distance is within the radius, add the sighting to the result
                if (current_dist <= radius) {
                    cout << current_dist << endl;
                    i.distance = current_dist;
                    result.push_back(i);
                }
            }
        }
    }

    return result;
}

// need to implement
vector<UFO::Row> UFO::mergeSort(vector<UFO::Row> vec, string datatype) {

    return vec;

}

// need to implement
vector<UFO::Row> UFO::quickSort(vector<UFO::Row> vec, string datatype) {

}

// temporary remove after implementing real sort
map<double, UFO::Row> UFO::tempSort(vector<UFO::Row> vec) {
    map<double, UFO::Row> temp_map;

    for (auto& sighting : vec) {
        temp_map[sighting.distance] = sighting;
    }

    return temp_map;
}



