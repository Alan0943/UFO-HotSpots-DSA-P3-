#include "UFO_Data.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//test
int main() {

    UFO ufo;

    // test insert
//    vector<std::string> vec = {
//            "11111City", "StateName", "CountryName", "Triangle", "5 minutes", "Bright light",
//            "33.6008333", "-85.831667", "2024", "10", "01", "14", "30",
//            "2024", "10", "01"
//    };
//    ufo.insert(33.6008333,-85.831667, vec);

//     testing keys
//    for (const auto& entry : test.grid_map) {
//        const pair<int, int>& key = entry.first;
//        cout << "Key: (" << key.first << ", " << key.second << ")" << endl;
//    }

//     testing indvidual key
//    for (const auto& sighting : test.grid_map[pair(30,-90)]) {
//        cout << "City: " << sighting.city << ", State: " << sighting.state << ", Country: "
//             << sighting.country << endl;
//    }

    // tests distanceCalc
    //cout << test.distanceCalc(33.6008333,-86.9561111,34.2022222,-87.1813889) << endl;


    // make a main menu, with a while loop that asks for input / outputs
    // menu item 1: user inputs coords, circle of area - outputs all sightings, sorted by distance
    // for sightings with same distance sort by time?
    // menu item 2: user inputs coords - outputs ALL sightings, sorted by distance
    // menu item 3: outputs all sightings sorted by duration length
    // menu item 4: outputs all sightings sorted by time


    string choice;
    string lat_str, lon_str, radius_str;
    double lat, lon, radius;

    while (true) {

        cout << "Welcome to the UFO Sightings Program!\n";
        cout << "1. View all sightings within a radius (max 500 miles) (input coordinates).\n";
        cout << "2. View cities with most sightings within a radius (max 500 miles) (input coordinates).\n";
        cout << "3. View Top 50 cities sorted by most sightings.\n";
        cout << "4. View Top 50 cities sorted by viewing duration.\n";
        cout << "5. Insert New Sighting.\n";

        cout << "6. Exit\n";

        cout << "Enter your choice:";
        cin >> choice;
        cout << endl;

        if (choice == "1") {

            // input
            cout << "Enter latitude:    ";
            cin >> lat_str;
            cout << endl;

            cout << "Enter longitude:   ";
            cin >> lon_str;
            cout << endl;

            cout << "Enter radius in miles: ";
            cin >> radius_str;
            cout << endl;

            // error checks for if it's a double or not
            try {
                lat = stod(lat_str);
                lon = stod(lon_str);
                radius = stod(radius_str);
            }
            catch (const std::invalid_argument& e) {
                cout << "Invalid input: Please enter valid numeric values for latitude, longitude, and radius." << endl;
            }

            // error checks distance
            if (lat > 50 || lat < 20 || lon < -130 || lon > -60 || radius > 501 || radius < 1) {
                cout << "Invalid Input: Radius <= 500, Lat 20-50, Lon -130 to -60." << endl;
                continue;
            }

            // gets all applicable sightings
            vector<UFO::Row> rows_vec = ufo.sortHelper(lat,lon,radius);

            // temporary need to implement real sort
            vector<UFO::Row> menu_1_output = ufo.tempSort(rows_vec, "distance");
            for (auto & i : menu_1_output) {
                cout << i.city << " " << i.state << " " << i.distance << endl;
            }

        }

        else if (choice == "2") {

            // input
            cout << "Enter latitude:    ";
            cin >> lat_str;
            cout << endl;

            cout << "Enter longitude:   ";
            cin >> lon_str;
            cout << endl;

            cout << "Enter radius in miles: ";
            cin >> radius_str;
            cout << endl;

            // error checks for if its a double or not
            try {
                lat = stod(lat_str);
                lon = stod(lon_str);
                radius = stod(radius_str);
            }
            catch (const std::invalid_argument& e) {
                cout << "Invalid input: Please enter valid numeric values for latitude, longitude, and radius." << endl;
            }

            // error checks distance
            if (lat > 50 || lat < 20 || lon < -130 || lon > -60 || radius > 501 || radius < 1) {
                cout << "Invalid Input: Radius <= 500, Lat 20-50, Lon -130 to -60." << endl;
                continue;
            }

            // gets all applicable sightings
            vector<UFO::Row> rows_vec = ufo.sortHelper(lat,lon,radius);

            // condenses rows_vec so thats its unique cities and each UFO::Row has city_count updated
            vector<UFO::Row> city_vec = ufo.sortHelper_2(rows_vec);

            // temporary sort
            vector<UFO::Row> menu_2_output = ufo.tempSort(city_vec, "city_count");
            for (auto & i : menu_2_output) {
                cout << i.city << " " << i.city_count << " " << i.distance << endl;
            }

        }

        else if (choice == "3") {

            // gets every single sighting in this vector
            vector<UFO::Row> UFO_all = ufo.grid_map_to_vec();

            // condenses UFO_all so that it is only unique cities and each UFO::Row has city_count updated
            vector<UFO::Row> city_vec = ufo.sortHelper_2(UFO_all);

            // temporary sort
            vector<UFO::Row> menu_3_output = ufo.tempSort(city_vec, "city_count_descend");
            for (int i = 0; i < 50; i++) {
                cout << menu_3_output[i].city << " " << menu_3_output[i].state << " " << menu_3_output[i].city_count << endl;
            }
        }

        else if (choice == "4") {

            // gets every single sighting in this vector
            vector<UFO::Row> UFO_all = ufo.grid_map_to_vec();

            // temp sort
            vector<UFO::Row> menu_4_output = ufo.tempSort(UFO_all, "duration");
            for (int i = 0; i < 50; i++) {
                cout << menu_4_output[i].city << " " << menu_4_output[i].state << " " << menu_4_output[i].duration << endl;
            }

        }

        else if (choice == "5") {

            // vector that stores all row attributes
            vector<string> insert_vec;

            cout << "Enter City (string): ";
            string city;
            cin >> city;
            insert_vec.push_back(city);

            cout << "Enter State (string): ";
            string state;
            cin >> state;
            insert_vec.push_back(state);

            cout << "Enter Country (string): ";
            string country;
            cin >> country;
            insert_vec.push_back(country);

            cout << "Enter Shape of UFO (string): ";
            string shape;
            cin >> shape;
            insert_vec.push_back(shape);

            cout << "Enter Duration (string): ";
            string duration;
            cin >> duration;
            insert_vec.push_back(duration);

            cout << "Enter Description (string): ";
            string description;
            cin >> description;
            insert_vec.push_back(description);

            cout << "Enter Latitude (double): ";
            string latitude;
            cin >> latitude;
            insert_vec.push_back(latitude);

            cout << "Enter Longitude (double): ";
            string longitude;
            cin >> longitude;
            insert_vec.push_back(longitude);

            cout << "Enter Year of Sight (string): ";
            string year;
            cin >> year;
            insert_vec.push_back(year);

            cout << "Enter Month of Sight (string): ";
            string month;
            cin >> month;
            insert_vec.push_back(month);

            cout << "Enter Day of Sight (string): ";
            string day;
            cin >> day;
            insert_vec.push_back(day);

            cout << "Enter Hour of Sight (string): ";
            string hour;
            cin >> hour;
            insert_vec.push_back(hour);

            cout << "Enter Minute of Sight (string): ";
            string minute;
            cin >> minute;
            insert_vec.push_back(minute);

            cout << "Enter Year of Documentation (string): ";
            string year_doc;
            cin >> year_doc;
            insert_vec.push_back(year_doc);

            cout << "Enter Month of Documentation (string): ";
            string month_doc;
            cin >> month_doc;
            insert_vec.push_back(month_doc);

            cout << "Enter Day of Documentation (string): ";
            string day_doc;
            cin >> day_doc;
            insert_vec.push_back(day_doc);

            // error checks
            try {
                ufo.insert(stod(insert_vec[6]), stod(insert_vec[7]), insert_vec);
            } catch (const std::invalid_argument& e) {
                cout << "Error: Invalid argument. Please enter valid numeric values for latitude and longitude." << endl;
            } catch (const exception& e) {
                cout << "Error: An unexpected error occurred: " << e.what() << endl;
            }
            continue;
        }

        else if (choice == "6") {
            cout << "end!" << endl;
            break;
        }

        else {
            cout << "Invalid Input - Insert a Number Between 1 and 6\n" << endl;
        }
    }
}


