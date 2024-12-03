#include "UFO_Data.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//test
int main() {

    UFO test;

    // test insert
    vector<std::string> vec = {
            "11111City", "StateName", "CountryName", "Triangle", "5 minutes", "Bright light",
            "33.6008333", "-85.831667", "2024", "10", "01", "14", "30",
            "2024", "10", "01"
    };
    test.insert(33.6008333,-85.831667, vec);

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

    // error check inputs

    int choice;
    double lat,lon,radius;
    vector<UFO::Row> temp;
    vector<UFO::Row> output;

    while (true) {
        cout << "Welcome to the UFO Sightings Program!\n";
        cout << "1. Search sightings by coordinates and radius\n";
        cout << "2. Search all sightings by coordinates\n";
        cout << "3. Show all sightings sorted by duration\n";
        cout << "4. Show all sightings sorted by time\n";
        cout << "5. Insert New Sighting\n";

        cout << "6. Exit\n";

        cout << "Enter your choice:";
        cin >> choice;
        cout << endl;

        if (choice == 1) {

            cout << "Enter latitude:    ";
            cin >> lat;
            cout << endl;

            cout << "Enter longitude:   ";
            cin >> lon;
            cout << endl;

            cout << "Enter radius in miles: ";
            cin >> radius;
            cout << endl;

            // error check
            if (lat > 50 || lat < 20 || lon < -130 || lon > -60 || radius > 501 || radius < 1) {
                cout << "Invalid Input" << endl;
                continue;
            }

            temp = test.sortHelper(lat,lon,radius);

            // temporary need to implement real sort
            map<double, UFO::Row> output = test.tempSort(temp);
            for (const auto& entry : output) {
                const UFO::Row& sighting = entry.second;
                cout << "City: " << sighting.city << ", State: " << sighting.state << ", Distance: "
                     << sighting.distance << endl;
            }

        }

        else if (choice == 2) {

            // error check
            cout << "Enter latitude: ";
            cin >> lat;
            cout << "Enter longitude: ";
            cin >> lon;

            temp = test.sortHelper(lat,lon,0);


//            output = test.mergeSort(temp, "distance");

            //display output

        }

        else if (choice == 6) {
            cout << "end!" << endl;
            break;
        }

        else {
            cout << "Invalid Input - Insert a Number Between 1 and 6\n" << endl;
        }
    }
}


